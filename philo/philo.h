/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-m-b <elel-m-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:45:58 by elel-m-b          #+#    #+#             */
/*   Updated: 2025/08/18 03:58:13 by elel-m-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h>
# include <stdatomic.h>

typedef struct s_table
{
	int				nph;
	int				td;
	int				te;
	int				ts;
	long			number_of_meals;
	int				is_death;
	pthread_mutex_t	*forks;
	long			start_time;
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	start;
}	t_table;

typedef struct s_philo
{
	int				id;
	pthread_t		threads;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
	pthread_mutex_t	eating_mutex;
	pthread_mutex_t	mutex_meals;
	long			last_meal_time;
	int				eating;
}	t_philo;

void	philo_message(t_philo *philo, const char *action);
int		start_simulation(t_philo *philos);
void	*routine(void *arg);
void	wait_philosophers(t_philo *philos);
int		parsing_args(char *argv[], t_table *table);
int		init_philosophers(t_philo *philos, t_table *table);
int		ft_numberlen(char *s);
int		check_args(int ac);
long	time_now(void);
long	ft_atoll(char *number);
void	philo_message(t_philo *philo, const char *message);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
int		monitor(t_philo *philos);
int		check_died(t_philo *philo);
void	ft_unlock(t_philo *philo);
void	asiigne_died(t_philo *philo);
void	put_error(char *err);
void	one_philosopher(t_philo *philo);
int		check_death(t_philo *philos, int i);
int		check_meals(t_philo *philos, int *count, int i);
int		ft_take_forks(t_philo *philo);
int		the_last(t_philo	*philo);
int		init_mutexes(t_table *table, t_philo *philos, int i);
void	init_philo_data(t_philo *philo, t_table *table, int i, int n_philo);
int		ft_usleep(long interval, t_philo *philo);
#endif
