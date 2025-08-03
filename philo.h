
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <limits.h>

#define FORK	"has taken a fork"
#define SLEEP	"is sleeping"
#define THINK	"is thinking"
#define EAT		"is eating"
#define DEAD	"died"

typedef     struct      s_table
{
    long long     nph;
    long long      td;
    long long     te;
    long long      ts;
    int     is_death;
    long long start_time;
    pthread_mutex_t	*forks;
    pthread_mutex_t	mutex_print;
}t_table;

typedef     struct      s_philo
{
    int     id;
    pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
    t_table     *table;
    long long    last_meal_time;
    int     eating;
    pthread_t       *threads;
}t_philo;
void	philog(t_philo *philo, const char *action);
void        start_similation(t_philo *philos);
void *routine(void *arg);
int     parsing_args(char **av, t_table *table);
void    wait_philosphers(t_philo *philos);
void init_philosophers(t_philo *philos, t_table *table);
int     ft_numberlen(char *s);
void        put_errro(char *err);
int     check_args(int ac);
long long	time_now(void);
int	ft_atoll(char	*number);