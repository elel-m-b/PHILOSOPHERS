#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int id = fork();
    int id2 = fork();
    int id3 = fork();

    printf("child pid %d  Parent pid %d\n", getpid(), getppid());
    fflush(stdout);   
    return 0;
}
