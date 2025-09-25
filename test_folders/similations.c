#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef     struct      s_table
{
    int     nph;
    int     td;
    int     te;
    int     ts;
    pthread_mutex_t	*forks;
}t_table;

typedef     struct      s_philo
{
    int     id;
    pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
    t_table     *table;
    pthread_t       *threads;
}t_philo;

int     ft_numberlen(char *s)
{
    int     i;
    i = 0;
    while (s[i])
        i++;
    return (i);
}

void        put_errro(char *err)
{
    write (2, err, ft_numberlen(err));
}

int     check_args(int ac)
{
    if (ac != 6 && ac != 5)
    {
        put_errro("Error\n");
        return (1);
    }
    return (0);
}

int	ft_atoll(char	*number)
{
	int	i;
	int	signe;
	int	res;

	i = 0;
	signe = 1;
	res = 0;
    while (number[i] == ' ' || (number[i] >= 9 && number[i] <= 13))
        i++;
	if (number[i] == '-')
	{
		signe = -1;
		i++;
	}
	else if (number[i] == '+')
		i++;
	while (number[i])
	{
        if (number[i] < '0' || number[i] > '9')
        {
            put_errro("Error\n");
            return (0);
        }
		res = res * 10 + (number[i] - '0');
		i++;
	}
	return (res * signe);
}

int     parsing_args(char **av, t_table *table)
{
    table->nph = ft_atoll(av[1]);
    table->td = ft_atoll(av[2]);
    table->te = ft_atoll(av[3]);
    table->ts = ft_atoll(av[4]);
    if (table->nph <= 0 || table->td < 0 || table->te < 0 || table->ts < 0)
    {
        put_errro ("Error\n");
        return (1);
    }
    return (0);
}

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
    return ;
}

int main(int        ac, char **av)
{
    t_table    table;
    t_philo     *philos;
    if (check_args(ac))
        return (1);
    if (parsing_args(av,&table))
        return (1);
    philos = malloc(sizeof(t_philo) * table.nph);
    if (!philos)
        put_errro("malloc failed\n");
    init_philosophers(philos, &table);
    start_similation(philos);
    wait_philosphers(philos);
    return (0);
}
