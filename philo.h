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

void        start_similation(t_philo *philos);
void *routine(void *arg);
int     parsing_args(char **av, t_table *table);
void    wait_philosphers(t_philo *philos);
void init_philosophers(t_philo *philos, t_table *table);
int     ft_numberlen(char *s);
void        put_errro(char *err);
int     check_args(int ac);
int	ft_atoll(char	*number);