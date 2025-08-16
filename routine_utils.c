/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-m-b <elel-m-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:28:12 by elel-m-b          #+#    #+#             */
/*   Updated: 2025/08/16 17:08:27 by elel-m-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	usleep(1000);
}

int	monitor(t_philo *philos)
{
	int		i;
	int		count;

	while (1)
	{
		i = -1;
		count = 0;
		while (++i < philos->table->nph)
		{
			pthread_mutex_lock(&(philos[i].mutex_meals));
			if (time_now() - philos[i].last_meal_time >= philos[i].table->td)
			{
				philo_message(&philos[i], "died");
				asiigne_died(philos);
				return (pthread_mutex_unlock(&(philos[i].mutex_meals)), 1);
			}
			pthread_mutex_unlock(&(philos[i].mutex_meals));
			pthread_mutex_lock(&(philos[i].eating_mutex));
			if (philos->table->number_of_meals > 0
				&& philos[i].eating >= philos->table->number_of_meals)
				count++;
			pthread_mutex_unlock(&(philos[i].eating_mutex));
		}
		if (philos->table->number_of_meals > 0
			&& count == philos->table->nph)
			return (asiigne_died(philos), 1);
	}
}

