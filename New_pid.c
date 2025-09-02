#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h> // Required for wait()

// Option 1: Same program, same code
void same_program_same_code()
{
    printf("Parent and child executing same code\n");
    pid_t pid = fork();
    if (pid == 0)
    {
        // Child process
        printf("Child PID: %d\n", getpid());
        exit(0); // Child exits after printing
    }
    else if (pid > 0)
    {
        // Parent process
        printf("Parent PID: %d\n", getpid());
        wait(NULL); // Wait for child to finish
    }
}

// Option 2: Same program, different code
void same_program_different_code()
{
    pid_t pid = fork();
    if (pid == 0)
    {
        printf("Child process code (PID: %d)\n", getpid());
        exit(0); // Child exits
    }
    else if (pid > 0)
    {
        printf("Parent process code (PID: %d)\n", getpid());
        wait(NULL); // Parent waits for child
    }
}

// Option 3: Parent waits for child
void wait_example()
{
    pid_t pid = fork();
    if (pid == 0)
    {
        printf("Child process code (PID: %d)\n", getpid());
        sleep(2);
        printf("Child process is done (PID: %d)\n", getpid());
        exit(0); // Child exits
    }
    else if (pid > 0)
    {
        printf("Parent process code is waiting (PID: %d)\n", getpid());
        wait(NULL); // Wait for child to finish
        printf("Parent process code is done (PID: %d)\n", getpid());
    }
}

int main()
{
    int ch;
    do
    {
        printf("\nMenu:\n");
        printf("1. Same program, same code\n");
        printf("2. Same program, different code\n");
        printf("3. Parent waits for child to finish task\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printf("\n--- Same code ---\n");
            same_program_same_code();
            break;
        case 2:
            printf("\n--- Different code ---\n");
            same_program_different_code();
            break;
        case 3:
            printf("\n--- Parent waits for child ---\n");
            wait_example();
            break;
        case 4:
            printf("Exiting......\n");
            break;
        default:
            printf("Try again.\n");
        }
    } while (ch != 4);

    return 0;
}
