#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>



// void        *f1(void *arg)
// {
//     printf ("the string is %s\n", (char *)(arg));
//     return (NULL);
// }


// void        *f2(void *arg)
// {
//     printf ("the string is %s\n", (char *)(arg));
//     return (NULL);
// }

// int main(void)
// {
//     char        *str = "HELLO WORLD FROM THREADS";
//     pthread_t       t1;
//     pthread_t       t2;
//     pthread_create(&t1, NULL, f1, str);
//     pthread_create(&t2, NULL, f2, str);
//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);
// }
void        take_fork()
{

}

void        realase_fork()
{

}

void        *philo_life(void        *arg)
{
    printf ("Hello from thread %d\n", *(int *)(arg));
    return (NULL);
}

int main(int ac, char **av)
{
    if (!av[1])
        return (0);
    int     i; 
    i = 0;
    int     num_p = atoi(av[1]);
    pthread_t       *p;
    p = malloc((sizeof(pthread_t)) * num_p);
    int     *id = malloc(num_p * sizeof(int));
    while (i++ < num_p)
        id[i] = i;
    i = 0;
    while (i < num_p)
    {
        int     j = i;
        pthread_create(&p[i], NULL, philo_life, &j);
        i++;
    }
    i = 0;
    while (i < num_p)
    {
        pthread_join(p[i], NULL);
        i++;
    }
}