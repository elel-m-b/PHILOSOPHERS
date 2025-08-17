/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_utilc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-m-b <elel-m-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:28:14 by elel-m-b          #+#    #+#             */
/*   Updated: 2025/08/17 11:13:19 by elel-m-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philos, int i)
{
	pthread_mutex_lock(&(philos[i].mutex_meals));
	if (time_now() - philos[i].last_meal_time >= philos[i].table->td)
	{
		philo_message(&philos[i], "died");
		asiigne_died(philos);
		pthread_mutex_unlock(&(philos[i].mutex_meals));
		return (1);
	}
	pthread_mutex_unlock(&(philos[i].mutex_meals));
	return (0);
}

int	check_meals(t_philo *philos, int *count, int i)
{
	pthread_mutex_lock(&(philos[i].eating_mutex));
	if (philos->table->number_of_meals > 0
		&& philos[i].eating >= philos->table->number_of_meals)
		(*count)++;
	pthread_mutex_unlock(&(philos[i].eating_mutex));
	return (0);
}

int	the_last(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	philo_message(philo, "has taken a fork");
	if (check_died(philo))
		return (pthread_mutex_unlock(philo->right_fork), 1);
	pthread_mutex_lock(philo->left_fork);
	philo_message(philo, "has taken a fork");
	if (check_died(philo))
		return (ft_unlock(philo), 1);
	return (0);
}

int	ft_take_forks(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (philo->id == table->nph)
		return (the_last(philo));
	pthread_mutex_lock(philo->left_fork);
	philo_message(philo, "has taken a fork");
	if (check_died(philo))
		return (pthread_mutex_unlock(philo->left_fork), 1);
	pthread_mutex_lock(philo->right_fork);
	philo_message(philo, "has taken a fork");
	if (check_died(philo))
		return (ft_unlock(philo), 1);
	return (0);
}

void	init_philo_data(t_philo *philo, t_table *table, int i, int n_philo)
{
	philo->table = table;
	philo->id = i + 1;
	philo->left_fork = &table->forks[i];
	philo->right_fork = &table->forks[(i + 1) % n_philo];
	philo->eating = 0;
	philo->last_meal_time = time_now();
}
