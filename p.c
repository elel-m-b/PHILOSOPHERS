#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>




int main(int ac, char **av)
{
    int     pid = fork();
    if (pid == 0)
        printf ("Hello world from child\n");
    else
        printf ("Hello world form parent\n");
}