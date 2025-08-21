/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-m-b <elel-m-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:28:12 by elel-m-b          #+#    #+#             */
/*   Updated: 2025/08/21 05:35:45 by elel-m-b         ###   ########.fr       */
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

void	ft_sleep(t_philo *philo, int time_to_sleep)
{
	philo_message(philo, "is sleeping");
	ft_usleep(time_to_sleep, philo);
}

void	ft_think(t_philo *philo)
{
	philo_message(philo, "is thinking");
	if (philo->table->nph % 2 && philo->table->te >= philo->table->ts)
		ft_usleep(philo->table->te, philo);
	else
		usleep(1000);
}

void	philo_message(t_philo *philo, const char *message)
{
	long	start;
	int		id;

	id = philo->id;
	start = philo->table->start_time;
	pthread_mutex_lock(&(philo->table->mutex_print));
	if (!check_died(philo))
		printf("%ld %d %s\n", time_now() - start, id, message);
	pthread_mutex_unlock(&(philo->table->mutex_print));
}

int	monitor(t_philo *philos)
{
	int	i;
	int	count;

	while (1)
	{
		i = 0;
		count = 0;
		while (i < philos->table->nph)
		{
			if (check_death(philos, i))
				return (1);
			check_meals(philos, &count, i);
			i++;
		}
		if (philos->table->number_of_meals > 0 && count == philos->table->nph)
			return (asiigne_died(philos), 1);
	}
}
