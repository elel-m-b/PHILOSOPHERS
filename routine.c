#include "philo.h"

void        print_message(int       id, int time, char *message)
{
    printf ("%d ", time);
    printf ("%d ", id);
    printf ("%s ", message);
    printf ("\n");
}
long long	time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void        ft_eat(t_philo *philo)
{
    philo->eating = 1;
    usleep(philo->table->te);
    pthread_mutex_lock(philo->left_fork);
    philo->last_meal_time = time_now();
    pthread_mutex_unlock(philo->right_fork);
    print_message(philo->id, time_now() - philo->start_time , EAT);
}
void    ft_sleep(t_philo *philo)
{
    print_message(philo->id, time_now(), SLEEP);
    usleep(philo->table->ts);
}
void    ft_think(t_philo *philo)
{
    usleep(1000);
    print_message (philo->id, time_now(), THINK);
}
void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_table     *table;

    table = philo->table;
    if (philo->id % 2 == 0)
        usleep(1000);
    while (!table->is_death)
    {
        ft_eat(philo);
        ft_sleep(philo);
        ft_think(philo);
    }
    return (NULL);
}
void init_philosophers(t_philo *philos, t_table *table)
{
    int     i;
    i = 0;
    int     n_philo = table->nph;
    philos->threads = malloc(sizeof(pthread_t) * table->nph);
    table->forks = malloc(sizeof(pthread_mutex_t) * table->nph);
    philos->start_time = time_now();
    while (i < table->nph)
    {
        pthread_mutex_init(&(table->forks[i]), NULL);
        philos[i].table = table;
        philos[i].id = i + 1;
		philos[i].left_fork= &(table->forks[i]);
        philos[i].right_fork = &(table->forks[(i + 1) % n_philo]);
        i++;
    }
}
int     monitor(t_philo *philo)
{
    while (1)
    {
        if (time_now() - philo->last_meal_time > philo->table->td)
        {
            philo->table->is_death = 0;
            return (philo->table->is_death);
        }
    }
    return (philo->table->is_death);
}
void    wait_philosphers(t_philo *philos)
{
    int     i;
    i = 0;
    while (i < philos->table->nph)
    {
        pthread_join(philos->threads[i], NULL);
        i++;
    }
}
void        start_similation(t_philo *philos)
{
    int     i;
    i = 0;
    while (i < philos->table->nph)
    {
        pthread_create(&philos->threads[i], NULL, routine, &philos[i]);
        i++;
    }
    monitor(philos);
    return ;
}