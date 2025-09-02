#include <stdio.h>
#include <sys/sysinfo.h>

int main()
{
    struct sysinfo info;
    if (sysinfo(&info) != 0)
    {
        printf("Error calling sysinfo");
        return 1;
    }
    long totalram = info.totalram / 1024;
    long freeram = info.freeram / 1024;
    long usedram = totalram - freeram;
    printf("Linux kernal memory info:\n");
    printf("Configured memory(totalram):%ldkB\n", totalram);
    printf("Free memory : %ldkB\n", freeram);
    printf("Used memory: %ldkB\n", usedram);
    return 0;
}