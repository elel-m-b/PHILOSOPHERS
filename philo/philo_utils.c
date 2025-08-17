/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-m-b <elel-m-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:08:45 by elel-m-b          #+#    #+#             */
/*   Updated: 2025/08/17 11:14:28 by elel-m-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_died(t_philo *philo)
{
	int	flag;

	pthread_mutex_lock(&(philo->table->mutex_death));
	flag = philo->table->is_death;
	pthread_mutex_unlock(&(philo->table->mutex_death));
	return (flag);
}

void	ft_unlock(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

long	time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	asiigne_died(t_philo *philo)
{
	pthread_mutex_lock(&(philo->table->mutex_death));
	philo->table->is_death = 1;
	pthread_mutex_unlock(&(philo->table->mutex_death));
}

int	init_mutexes(t_table *table, t_philo *philos, int i)
{
	if (pthread_mutex_init(&table->forks[i], NULL)
		|| pthread_mutex_init(&philos[i].mutex_meals, NULL)
		|| pthread_mutex_init(&philos[i].eating_mutex, NULL))
		return (1);
	return (0);
}
