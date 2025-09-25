#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
// int     identify_process(void)
// {
//     int pid = fork();
//     if (pid == 0)
//         return (0);
//     return (1);
// }

// int main(void)
// {
//     int     a = identify_process();
//     if (a == 1)
//         printf ("we are in parent\n");
//     else 
//         printf ("we are in child process\n");
// }

// void        wait_for_child(void)
// {
//     int     a;
//     a = 0;
//     int  pid = fork();
//     if (pid == 0)
//     {
//         while (1)
//             printf ("Hello world from %d\n", pid);
//         printf ("child is finished\n");
//         exit(0);
//     }
//     else
//     {
//         int pid_of_child = wait(NULL);
//         printf ("Hello I am parent and pid of child is %d\n", pid_of_child);
//     }
// }

// int main(void)
// {
//     wait_for_child();
// }

int     get_child_exit_code(void)
{
    printf ("%d\n", getpid());
    int     pid = fork();
    int     pid2 = fork();
    printf ("%d\n", pid);
    if (pid == 0)
        printf ("I am child %d\n", pid);
    return (pid);
}

int main()
{
    get_child_exit_code();
}