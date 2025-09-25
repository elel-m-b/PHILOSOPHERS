#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// int main()
// {
//     printf ("the parent process main process is %d\n", getpid());
//     int id = fork();
//     int id2 = fork();
//     int id3 = fork();

//     printf("PID: %d | PPID: %d | id: %d | id2: %d | id3: %d\n",  getpid(), getppid(), id, id2, id3);
//     return 0;
// }


int main()
{
    printf ("the main process is %d\n", getpid());
    int     a = fork();
    int     b = fork();
    printf("PID %d || a = %d || b = %d\n", getpid(), a, b);
}