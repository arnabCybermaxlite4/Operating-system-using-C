#include <stdio.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

int main() {
    int n;
    float avgTurnaround = 0, avgWaiting = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time for Process P%d: ", p[i].pid);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
    }

    // Sort by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrivalTime > p[j + 1].arrivalTime) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // FCFS Logic
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].arrivalTime) {
            currentTime = p[i].arrivalTime;
        }
        p[i].completionTime = currentTime + p[i].burstTime;
        p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;

        avgTurnaround += p[i].turnaroundTime;
        avgWaiting += p[i].waitingTime;

        currentTime = p[i].completionTime;
    }

    // Output table
    printf("\n--- FCFS Scheduling without Gantt Chart ---\n");
    printf("-------------------------------------------------------------\n");
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
            p[i].pid, p[i].arrivalTime, p[i].burstTime,
            p[i].completionTime, p[i].turnaroundTime, p[i].waitingTime);
    }

    printf("-------------------------------------------------------------\n");
    printf("Average Turnaround Time : %.2f\n", avgTurnaround / n);
    printf("Average Waiting Time    : %.2f\n", avgWaiting / n);

    return 0;
}
