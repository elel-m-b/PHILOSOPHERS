#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


// 1  Parent Waits for Child


// int main(int        ac, char        **av)
// {
//     int     pid = fork();
//     if (pid == 0)
//     {
//         int     i;
//         i = 0;
//         while (i < 20)
//         {
//             printf ("%d .Hello world\n", i);
//             i++;
//         }
//     }
//     int     j;
//     j = 0;
//     while (j < 10)
//     {
//         printf ("%d .OK\n", j);
//         j++;
//     }
// }

int main()
{
    int     pid = fork();
    int     j = fork();
    printf ("Hello world\n");
}

// int main(int ac, char **av)
// {
//     int     x = 0;
//     int     j;
//     j = 0;
//     int     pid = fork();
//     while (j <= 100)
//         j++;
//     printf("the pid is %d\n", pid);
//     if (pid == 0)
//     {
//         x = x + 10;
//         printf ("Hello world from child\n");
//     }
//     else
//         printf ("Hello world form parent\n");
//     printf ("the value of x is %d\n", x);
//     printf ("the value of j is %d\n", j);
// }