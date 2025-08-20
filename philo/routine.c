/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-m-b <elel-m-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:46:09 by elel-m-b          #+#    #+#             */
/*   Updated: 2025/08/20 23:21:01 by elel-m-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (ft_take_forks(philo))
		return (1);
	philo_message(philo, "is eating");
	pthread_mutex_lock(&philo->eating_mutex);
	philo->eating++;
	pthread_mutex_unlock(&philo->eating_mutex);
	pthread_mutex_lock(&philo->mutex_meals);
	philo->last_meal_time = time_now();
	pthread_mutex_unlock(&philo->mutex_meals);
	ft_usleep(table->te, philo);
	ft_unlock(philo);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->start);
	pthread_mutex_unlock(&philo->table->start);
	table = philo->table;
	if (table->nph == 1)
		return (one_philosopher(philo), NULL);
	if (philo->id % 2 == 0)
		usleep(5000);
	while (!check_died(philo))
	{
		if (ft_eat(philo))
			return (NULL);
		ft_sleep(philo, table->ts);
		ft_think(philo);
	}
	return (NULL);
}

int	init_philosophers(t_philo *philos, t_table *table)
{
	int	i;
	int	n_philo;

	n_philo = table->nph;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nph);
	if (!table->forks)
		return (put_error("malloc failed\n"), 1);
	table->start_time = time_now();
	pthread_mutex_init(&table->mutex_print, NULL);
	pthread_mutex_init(&table->mutex_death, NULL);
	table->is_death = 0;
	i = -1;
	while (++i < table->nph && !init_mutexes(table, philos, i))
		init_philo_data(&philos[i], table, i, n_philo);
	return (0);
}

void	wait_philosophers(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->table->nph)
	{
		pthread_join(philos[i].threads, NULL);
		i++;
	}
}

int	start_simulation(t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_init(&philos->table->start, NULL);
	pthread_mutex_lock(&philos->table->start);
	while (i < philos->table->nph)
	{
		if (pthread_create(&philos[i].threads, NULL, routine, &philos[i]))
		{
			while (--i >= 0)
				pthread_join(philos[i].threads, NULL);
			destroy_all_mutexes(philos);
			return (put_error("failed to create threads\n"), 1);
		}
		i++;
	}
	pthread_mutex_unlock(&philos->table->start);
	monitor(philos);
	return (0);
}
