/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-m-b <elel-m-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:28:12 by elel-m-b          #+#    #+#             */
/*   Updated: 2025/08/16 19:57:14 by elel-m-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philosopher(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	philo_message(philo, "has taken a fork");
	usleep(philo->table->td * 1000);
	philo_message(philo, "died");
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_message(t_philo *philo, const char *message)
{
	long	interval;
	long	start;
	int		id;

	interval = 0;
	id = philo->id;
	start = philo->table->start_time;
	interval = time_now() - start;
	pthread_mutex_lock(&(philo->table->mutex_print));
	if (!check_died(philo))
		printf("%ld %d %s\n", interval, id, message);
	pthread_mutex_unlock(&(philo->table->mutex_print));
}

void	ft_sleep(t_philo *philo)
{
	philo_message(philo, "is sleeping");
	usleep(philo->table->ts * 1000);
}

void	ft_think(t_philo *philo)
{
	philo_message(philo, "is thinking");
	if (philo->table->te > philo->table->ts)
		usleep(philo->table->te * 1000);
	usleep(1000);
}

int	monitor(t_philo *philos)
{
	int	i;
	int	count;

	while (1)
	{
		i = -1;
		count = 0;
		while (++i < philos->table->nph)
		{
			if (check_death(philos, i))
				return (1);
			check_meals(philos, &count, i);
		}
		if (philos->table->number_of_meals > 0 && count == philos->table->nph)
			return (asiigne_died(philos), 1);
	}
}
