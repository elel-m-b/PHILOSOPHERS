#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>




int main(int ac, char **av)
{
    int     pid = fork();
    printf ("Hello world\n");
}