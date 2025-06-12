#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


int     identify_process(void)
{
    int pid = fork();
    if (pid == 0)
        return (0);
    return (1);
}

int main(void)
{
    int     a = identify_process();
    if (a == 1)
        printf ("we are in parent\n");
    else 
        printf ("we are in child process\n");
}