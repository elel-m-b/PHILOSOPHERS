#include "philo.h"

void	philog(t_philo *philo, const char *action)
{
	long long	interval;
	long long	start;
	int			id;

	interval = 0;
	id = philo->id;
	start = philo->start_time;
	interval = time_now() - start;
	if (philo->table->is_death)
		return ;
	pthread_mutex_lock(&(philo->table->mutex_print));
	if (!philo->table->is_death)
		printf("%lld %d %s\n", interval, id, action);
	if (*action == 'd')
		philo->table->is_death = 1;
	pthread_mutex_unlock(&(philo->table->mutex_print));
}
long long	time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(philo->left_fork);
	philog(philo, FORK);
	pthread_mutex_lock(philo->right_fork);
    philog(philo, FORK);
	philog(philo, EAT);
    philo->last_meal_time = time_now();
    usleep(philo->table->te); 
    pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}
void    ft_sleep(t_philo *philo)
{
    philog(philo, SLEEP);
    usleep(philo->table->ts);
}
void    ft_think(t_philo *philo)
{
    philog(philo, THINK);
    usleep(1000);
}
void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_table     *table;

    table = philo->table;
    if (philo->id % 2 == 0)
        usleep(100);
    while (table->is_death)
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
    pthread_mutex_init(&(table->mutex_print), NULL);
    while (i < table->nph)
    {
        pthread_mutex_init(&(table->forks[i]), NULL);
        philos[i].table = table;
        philos[i].id = i + 1;
        philos->table->is_death = 0;
		philos[i].left_fork= &(table->forks[i]);
        philos[i].right_fork = &(table->forks[(i + 1) % n_philo]);
        philos[i].last_meal_time = time_now();
        i++;
    }
}
int monitor(t_philo *philos)
{
    int i;
    while (1)
    {
        i = 0;
        while (i < philos->table->nph)
        {
            if (time_now() - philos[i].last_meal_time > philos[i].table->td)
            {
                philos->table->is_death = 1;
                philog(&philos[i], "died");
                return 1;
            }
            i++;
        }
        usleep(1000);
    }
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
