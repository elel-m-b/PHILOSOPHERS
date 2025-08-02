#include "philo.h"

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    printf("Hello from philo %d\n", philo->id);
    return (NULL);
}

void init_philosophers(t_philo *philos, t_table *table)
{
    int     i;
    i = 0;
    int     n_philo = table->nph;
    philos->threads = malloc(sizeof(pthread_t) * table->nph);
    table->forks = malloc(sizeof(pthread_mutex_t) * table->nph);
    while (i < table->nph)
    {
        pthread_mutex_init(&(table->forks[i]), NULL);
        philos[i].table = table;
        philos->id = i + 1;
		philos[i].left_fork= &(table->forks[i]);
        philos[i].right_fork = &(table->forks[(i + 1) % n_philo]);
        i++;
    }
    i = 0;
    while (i < philos->table->nph)
    {
        pthread_create(&philos->threads[i], NULL, routine, &philos[i]);
        i++;
    }
}
