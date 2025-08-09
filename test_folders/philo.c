#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
typedef	struct	s_philo
{
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_philo;
	pthread_t	*thread;
	pthread_mutex_t	*mutex;
	int		id;
	int		left_fork;
	int		right_fork;
}t_philo;
void print_error_and_exit()
{
	printf("Error in argument\n");
	exit(1);
}

int ft_atoi(char *str)
{
	int i = 0;
	int res = 0;
	
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			print_error_and_exit();
		i++;
	}
	
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

void		*philo_routine(void	*arg)
{
	t_philo *philo = (t_philo *)arg;
	printf("Philo %d is thinking\n", philo->id);
	printf("Philo %d has taken a left_fork %d\n", philo->id, philo->left_fork);
	printf("Philo %d has taken a right fork %d\n", philo->id, philo->right_fork);
	printf("Philo %d is eating\n", philo->id);
	printf("Philo %d is sleeping\n", philo->id);	
	return (NULL);
}

int main(int ac, char **av)
{
	int		i; 
	i = 0;
	t_philo table;
	t_philo		*philo;
	if (ac == 5 || ac == 6)
	{
		table.number_of_philo = ft_atoi(av[1]);
		table.time_to_die = ft_atoi(av[2]);
		table.time_to_eat = ft_atoi(av[3]);
		table.time_to_sleep = ft_atoi(av[4]);
	}
	else
		print_error_and_exit();
	table.thread = malloc(sizeof(pthread_t) * table.number_of_philo);
	table.mutex = malloc(sizeof(pthread_mutex_t) * table.number_of_philo);
	while (i < table.number_of_philo)
	{
		if (pthread_mutex_init(&table.mutex[i], NULL) != 0)
			print_error_and_exit();
		i++;
	}
	philo = malloc(sizeof(t_philo) * table.number_of_philo);
	if (!philo)
		print_error_and_exit();
	i = 0;
	while (i < table.number_of_philo)
	{
		philo[i].id = i;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % table.number_of_philo;
		pthread_create(&table.thread[i], NULL, philo_routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < table.number_of_philo)
	{
		pthread_join(table.thread[i], NULL);
		i++;
	}
}
