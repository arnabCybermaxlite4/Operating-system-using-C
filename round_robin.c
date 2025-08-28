#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int pid, at, bt, ct, tat, wt, rt, done;
} P;

void print_table(P p[], int n)
{
    printf("\n--------------------------------------------------------------------------------------------\n");
    printf("%43s\n", "Process Table");
    printf("--------------------------------------------------------------------------------------------\n");
    printf("| PID  | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |\n");
    printf("--------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
        printf("| P%-3d | %12d | %10d | %15d | %15d | %12d |\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    printf("--------------------------------------------------------------------------------------------\n");
}

int main()
{
    int n, choice, tq;
    printf("Number of processes: ");
    scanf("%d", &n);
    printf("Enter arrival times? (1-Yes, 0-No): ");
    scanf("%d", &choice);
    printf("Time quantum: ");
    scanf("%d", &tq);

    P *p = (P *)malloc(n * sizeof(P));
    if (!p)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        if (choice == 1)
        {
            printf("Arrival P%d: ", i + 1);
            scanf("%d", &p[i].at);
        }
        else
        {
            p[i].at = 0;
        }
        printf("Burst P%d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].done = 0;
        p[i].ct = p[i].tat = p[i].wt = 0;
    }

    // Ready queue (store process indices)
    int *rq = (int *)malloc(10000 * sizeof(int));
    int front = 0, back = 0;
    int *inq = (int *)calloc(n, sizeof(int));

    int time = 0, completed = 0;
    double total_tat = 0, total_wt = 0;

    // If no arrivals at 0, jump to earliest arrival
    if (choice == 1)
    {
        int earliest = 1e9;
        for (int i = 0; i < n; i++)
            if (p[i].at < earliest)
                earliest = p[i].at;
        time = earliest;
    }

    // Seed queue with jobs arrived by current time
    for (int i = 0; i < n; i++)
    {
        if (!p[i].done && p[i].at <= time && !inq[i])
        {
            rq[back++] = i;
            inq[i] = 1;
        }
    }

    while (completed < n)
    {
        // If queue empty, advance time to next arrival
        if (front == back)
        {
            int next_t = 1e9, idx = -1;
            for (int i = 0; i < n; i++)
            {
                if (!p[i].done && !inq[i] && p[i].at > time && p[i].at < next_t)
                {
                    next_t = p[i].at;
                    idx = i;
                }
            }
            if (idx != -1)
            {
                time = next_t;
                rq[back++] = idx;
                inq[idx] = 1;
            }
            else
            {
                // All remaining either arrived or in queue; nothing to enqueue
                // To avoid deadlock, enqueue any available
                for (int i = 0; i < n; i++)
                {
                    if (!p[i].done && !inq[i] && p[i].at <= time)
                    {
                        rq[back++] = i;
                        inq[i] = 1;
                    }
                }
                if (front == back)
                    break; // safety
            }
            continue;
        }

        int i = rq[front++]; // dequeue
        int slice = p[i].rt < tq ? p[i].rt : tq;

        int old_time = time;
        time += slice;
        p[i].rt -= slice;

        // Enqueue any newly arrived during (old_time, time]
        for (int k = 0; k < n; k++)
        {
            if (!p[k].done && !inq[k] && p[k].at <= time)
            {
                rq[back++] = k;
                inq[k] = 1;
            }
        }

        if (p[i].rt == 0)
        {
            p[i].done = 1;
            p[i].ct = time;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
            total_tat += p[i].tat;
            total_wt += p[i].wt;
            inq[i] = 0;
            completed++;
        }
        else
        {
            // time slice over, requeue current
            rq[back++] = i;
        }
    }

    print_table(p, n);
    printf("\nAverage Turnaround Time: %.2f\nAverage Waiting Time: %.2f\n", total_tat / n, total_wt / n);

    free(rq);
    free(inq);
    free(p);
    return 0;
}