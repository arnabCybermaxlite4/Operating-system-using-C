#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

int main()
{
    struct utsname sysinfo;
    if (uname(&sysinfo) == 0)
    {
        printf("Kernal Version: %s\n", sysinfo.release);
    }
    else
    {
        perror("\n Error getting kernal information");
    }

    printf("\nCpu information:\n");
    system("grep -m 1 'model name' /proc/cpuinfo");
    return 0;
}