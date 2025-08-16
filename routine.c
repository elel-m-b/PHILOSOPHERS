/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-m-b <elel-m-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:46:09 by elel-m-b          #+#    #+#             */
/*   Updated: 2025/08/16 17:39:06 by elel-m-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(philo->left_fork);
	philo_message(philo, "has taken a fork");
	if (check_died(philo))
		return (pthread_mutex_unlock(philo->left_fork), 1);
	pthread_mutex_lock(philo->right_fork);
	philo_message(philo, "has taken a fork");
	if (check_died(philo))
		return (ft_unlock(philo), 1);
	philo_message(philo, "is eating");
	pthread_mutex_lock(&(philo->eating_mutex));
	philo->eating++;
	pthread_mutex_unlock(&(philo->eating_mutex));
	pthread_mutex_lock(&(philo->mutex_meals));
	philo->last_meal_time = time_now();
	pthread_mutex_unlock(&(philo->mutex_meals));
	usleep(table->te * 1000);
	ft_unlock(philo);
	return (0);
}

void	one_philosopher(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	philo_message(philo, "has taken a fork");
	usleep(philo->table->td * 1000);
	philo_message(philo, "died");
	pthread_mutex_unlock(philo->left_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (table->nph == 1)
		return (one_philosopher(philo), NULL);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!check_died(philo))
	{
		ft_think(philo);
		if (ft_eat(philo))
			return (NULL);
		ft_sleep(philo);
	}
	return (NULL);
}

void	init_philosophers(t_philo *philos, t_table *table)
{
	int	i;
	int	n_philo;

	i = 0;
	n_philo = table->nph;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nph);
	table->start_time = time_now();
	pthread_mutex_init(&(table->mutex_print), NULL);
	pthread_mutex_init(&(table->mutex_death), NULL);
	while (i < table->nph)
	{
		pthread_mutex_init(&(table->forks[i]), NULL);
		pthread_mutex_init(&(philos[i].mutex_meals), NULL);
		pthread_mutex_init(&(philos[i].eating_mutex), NULL);
		philos[i].table = table;
		philos[i].id = i + 1;
		philos[i].left_fork = &(table->forks[i]);
		table->is_death = 0;
		philos[i].right_fork = &(table->forks[(i + 1) % n_philo]);
		philos[i].eating = 0;
		philos[i].last_meal_time = time_now();
		i++;
	}
}

void	wait_philosphers(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->table->nph)
	{
		pthread_join(philos[i].threads, NULL);
		i++;
	}
}

void	start_similation(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->table->nph)
	{
		pthread_create(&philos[i].threads, NULL, routine, &philos[i]);
		i++;
	}
	monitor(philos);
}

