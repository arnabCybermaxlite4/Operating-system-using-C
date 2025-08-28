#include <stdio.h>
#include <stdlib.h>

static void print_alloc(const char *title, int alloc[], int n, int remBlock[], int m)
{
    printf("\n%s\n", title);
    printf("-------------------------------------------------\n");
    printf("| Process | Allocated Block | Remaining in Block |\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        if (alloc[i] == -1)
        {
            printf("| P%-6d| %-15s | %-18s |\n", i + 1, "Not Allocated", "-");
        }
        else
        {
            int b = alloc[i];
            printf("| P%-6d| B%-14d | %-18d |\n", i + 1, b + 1, remBlock[b]);
        }
    }
    printf("-------------------------------------------------\n");
}

static void first_fit(const int blockSize[], int m, const int procSize[], int n, int outAlloc[], int outRem[])
{
    for (int i = 0; i < m; i++)
        outRem[i] = blockSize[i];
    for (int i = 0; i < n; i++)
        outAlloc[i] = -1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (outRem[j] >= procSize[i])
            {
                outRem[j] -= procSize[i];
                outAlloc[i] = j;
                break;
            }
        }
    }
}

static void best_fit(const int blockSize[], int m, const int procSize[], int n, int outAlloc[], int outRem[])
{
    for (int i = 0; i < m; i++)
        outRem[i] = blockSize[i];
    for (int i = 0; i < n; i++)
        outAlloc[i] = -1;
    for (int i = 0; i < n; i++)
    {
        int best = -1;
        for (int j = 0; j < m; j++)
        {
            if (outRem[j] >= procSize[i])
            {
                if (best == -1 || outRem[j] < outRem[best])
                    best = j;
            }
        }
        if (best != -1)
        {
            outRem[best] -= procSize[i];
            outAlloc[i] = best;
        }
    }
}

static void worst_fit(const int blockSize[], int m, const int procSize[], int n, int outAlloc[], int outRem[])
{
    for (int i = 0; i < m; i++)
        outRem[i] = blockSize[i];
    for (int i = 0; i < n; i++)
        outAlloc[i] = -1;
    for (int i = 0; i < n; i++)
    {
        int worst = -1;
        for (int j = 0; j < m; j++)
        {
            if (outRem[j] >= procSize[i])
            {
                if (worst == -1 || outRem[j] > outRem[worst])
                    worst = j;
            }
        }
        if (worst != -1)
        {
            outRem[worst] -= procSize[i];
            outAlloc[i] = worst;
        }
    }
}

static void input_data(int **blockSize, int *m, int **procSize, int *n)
{
    printf("Enter number of memory blocks: ");
    scanf("%d", m);
    free(*blockSize);
    *blockSize = (int *)malloc((*m) * sizeof(int));
    if (!*blockSize)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    printf("Enter sizes of %d blocks:\n", *m);
    for (int i = 0; i < *m; i++)
        scanf("%d", &(*blockSize)[i]);

    printf("Enter number of processes: ");
    scanf("%d", n);
    free(*procSize);
    *procSize = (int *)malloc((*n) * sizeof(int));
    if (!*procSize)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    printf("Enter sizes of %d processes:\n", *n);
    for (int i = 0; i < *n; i++)
        scanf("%d", &(*procSize)[i]);
}

static void run_first_fit(const int *blockSize, int m, const int *procSize, int n)
{
    int *alloc = (int *)malloc(n * sizeof(int));
    int *rem = (int *)malloc(m * sizeof(int));
    if (!alloc || !rem)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    first_fit(blockSize, m, procSize, n, alloc, rem);
    print_alloc("First Fit Allocation", alloc, n, rem, m);
    free(alloc);
    free(rem);
}

static void run_best_fit(const int *blockSize, int m, const int *procSize, int n)
{
    int *alloc = (int *)malloc(n * sizeof(int));
    int *rem = (int *)malloc(m * sizeof(int));
    if (!alloc || !rem)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    best_fit(blockSize, m, procSize, n, alloc, rem);
    print_alloc("Best Fit Allocation", alloc, n, rem, m);
    free(alloc);
    free(rem);
}

static void run_worst_fit(const int *blockSize, int m, const int *procSize, int n)
{
    int *alloc = (int *)malloc(n * sizeof(int));
    int *rem = (int *)malloc(m * sizeof(int));
    if (!alloc || !rem)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    worst_fit(blockSize, m, procSize, n, alloc, rem);
    print_alloc("Worst Fit Allocation", alloc, n, rem, m);
    free(alloc);
    free(rem);
}

int main()
{
    int *blockSize = NULL, *procSize = NULL;
    int m = 0, n = 0, choice;

    // Initial input once; can be re-entered via menu
    input_data(&blockSize, &m, &procSize, &n);

    do
    {
        printf("\n====== Memory Allocation Menu ======\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Worst Fit\n");
        printf("4. Run All (FF, BF, WF)\n");
        printf("5. Re-enter Blocks/Processes\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Exiting.\n");
            break;
        }

        switch (choice)
        {
        case 1:
            run_first_fit(blockSize, m, procSize, n);
            break;
        case 2:
            run_best_fit(blockSize, m, procSize, n);
            break;
        case 3:
            run_worst_fit(blockSize, m, procSize, n);
            break;
        case 4:
            run_first_fit(blockSize, m, procSize, n);
            run_best_fit(blockSize, m, procSize, n);
            run_worst_fit(blockSize, m, procSize, n);
            break;
        case 5:
            input_data(&blockSize, &m, &procSize, &n);
            break;
        case 6:
            printf("Exiting..........");
            break;
        default:
            printf("Please enter a valid choice (0-5).\n");
        }
    } while (choice != 6);

    free(blockSize);
    free(procSize);
    return 0;
}