/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-m-b <elel-m-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:45:58 by elel-m-b          #+#    #+#             */
/*   Updated: 2025/08/10 14:34:10 by elel-m-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <limits.h>

typedef     struct      s_table
{
	long     nph;
	long      td;
	long     te;
	long      ts;
	long        number_of_meals;
	_Atomic int     is_death;
	pthread_mutex_t	*forks;
	_Atomic long long start_time;
	pthread_mutex_t	mutex_meals;
	pthread_mutex_t	mutex_print;
}t_table;

typedef     struct      s_philo
{
	int     id;
	unsigned long int       *threads;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_table     *table;
	_Atomic long    last_meal_time;
	_Atomic int     eating;
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
long	time_now(void);
int	ft_atoll(char	*number);
long	time_now(void);
void	philog(t_philo *philo, const char *message);
void    ft_sleep(t_philo *philo);
void    ft_think(t_philo *philo);
int monitor(t_philo *philos);
