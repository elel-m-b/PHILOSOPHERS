#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void        *ft_routine(char *arg)
{
    int     id = *(int *)(arg);
    printf ("hello from thread %d\n", id);
    return (NULL);
}

int main(int        ac, char **av)
{
    if (ac >= 2)
        return 0;
    int     i;
    i = 0;
    int         n = atoi(av[1]);
    pthread_t       *thread = malloc(sizeof(pthread_t) * n);
    while (i < n)
    {
        int     id = i;
        pthread_create(&thread[i], NULL, ft_routine, &id);
        i++;
    }
    i = 0;
    while (i < n)
    {
        pthread_join(thread[i], NULL);
        i++;
    }
    return (0);
}