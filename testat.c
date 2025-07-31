#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// typedef struct philo
// {
//     int         id;
//     int     globle_varr;
//     pthread_t   thread;
// } t_philo;

// void *routine(void *arg)
// {
//     t_philo *philo = (t_philo *)(arg);
//     printf("the id is %d\n", philo->id);
//     return NULL;
// }

// int main()
// {
//     int i = 0;
//     t_philo *philos = malloc(sizeof(t_philo) * 10);
//     if (!philos)
//         return 1;

//     while (i < 10)
//     {
//         philos->globle_varr = 1;
//         philos[i].id = i + 1;
//         pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
//         i++;
//     }

//     i = 0;
//     while (i < 10)
//     {
//         pthread_join(philos[i].thread, NULL);
//         i++;
//     }
//     return 0;
// }

// int ft_strlen(char *s)
// {
//     int     i;
//     i  = 0;
//     while (s[i])
//         i++;
//     return (i);
// }
// void        *helper(void *arg)
// {
//     char    *v = (char *)(arg);
//     printf ("the pointer are |%s|\n", v);
//     int         *i = malloc(4);
//     while (v[*i])
//         (*i)++;
//     return (i);
// }

// int main()
// {
//     pthread_t   t1;
//     pthread_t   t2;

//     void      *i;
//     pthread_create(&t1, NULL, helper, "Hello world");
//     pthread_join(t1, &i);
//     printf ("the res are %d\n", *(int *)(i));
// }

void        *routine(void *arg)
{
    int    *num = malloc(4);
    *num = 42;
    return (num);
}
void        *routine_two(void *arg)
{
    int     *ha = (int *)(arg);
    free(ha);
    printf ("ok\n");
    return (NULL);
}

int main()
{
    void *res;
    pthread_t       t1;
    pthread_t       t2;
    pthread_create(&t1, NULL, routine, NULL);
    pthread_join(t1, &res);
    pthread_create(&t2, NULL, routine_two, res);
    pthread_join(t2, NULL);
    printf("the res are |%d|\n", *(int *)res);
}