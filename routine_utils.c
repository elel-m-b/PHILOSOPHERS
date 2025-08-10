/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-m-b <elel-m-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:28:12 by elel-m-b          #+#    #+#             */
/*   Updated: 2025/08/10 14:30:08 by elel-m-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	philog(t_philo *philo, const char *message)
{
	long	interval;
	long	start;
	int			id;

	interval = 0;
	id = philo->id;
	start = philo->table->start_time;
	interval = time_now() - start;
	pthread_mutex_lock(&(philo->table->mutex_print));
	if (!philo->table->is_death)
		printf("%ld %d %s\n", interval, id, message);
	if (*message == 'd')
		philo->table->is_death = 1;
	pthread_mutex_unlock(&(philo->table->mutex_print));
}

void    ft_sleep(t_philo *philo)
{
	philog(philo, SLEEPPING);
	usleep(philo->table->ts * 1000);
}
void    ft_think(t_philo *philo)
{
	philog(philo, THINKING);
}

int monitor(t_philo *philos)
{
	int i;
	int count;

	while (1)
	{
		i = 0;
		count = 0;
		while (i < philos->table->nph)
		{
			if (time_now() - philos[i].last_meal_time >= philos[i].table->td)
			{
				philog(&philos[i], DEAD);
				philos->table->is_death = 1;
				return 1;
			}
			else if (philos->table->number_of_meals > 0 && philos[i].eating >= philos->table->number_of_meals)
				count++;
			i++;
		}
		if (philos->table->number_of_meals > 0 && count == philos->table->nph)
			philos->table->is_death = 1;
	}
}