/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-m-b <elel-m-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:45:58 by elel-m-b          #+#    #+#             */
/*   Updated: 2025/08/16 17:29:36 by elel-m-b         ###   ########.fr       */
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
	long			nph;
	long			td;
	long			te;
	long			ts;
	long			number_of_meals;
	int				is_death;
	pthread_mutex_t	*forks;
	long long		start_time;
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	mutex_print;
}	t_table;

typedef struct s_philo
{
	int				id;
	pthread_t		*threads;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
	pthread_mutex_t	eating_mutex;
	pthread_mutex_t	mutex_meals;
	long			last_meal_time;
	int				eating;
}	t_philo;

void	philo_message(t_philo *philo, const char *action);
void	start_similation(t_philo *philos);
void	*routine(void *arg);
int		parsing_args(char **av, t_table *table);
void	wait_philosphers(t_philo *philos);
void	init_philosophers(t_philo *philos, t_table *table);
int		ft_numberlen(char *s);
int		check_args(int ac);
long	time_now(void);
long		ft_atoll(char *number);
void	philo_message(t_philo *philo, const char *message);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
int		monitor(t_philo *philos);
int		check_died(t_philo *philo);
void	ft_unlock(t_philo *philo);
void	asiigne_died(t_philo *philo);
void        put_error(char *err);
#endif
