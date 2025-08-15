/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-m-b <elel-m-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:08:04 by elel-m-b          #+#    #+#             */
/*   Updated: 2025/08/15 14:14:50 by elel-m-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	destroy_all_mutexes(t_philo *philo)
{
	int		i;

	i = 0;
	while (i < philo->table->nph)
	{
		pthread_mutex_destroy(&philo->table->forks[i]);
		pthread_mutex_destroy(&philo[i].mutex_meals);
		pthread_mutex_destroy(&philo[i].eating_mutex);
		i++;
	}
	pthread_mutex_destroy(&philo->table->mutex_print);
	pthread_mutex_destroy(&philo->table->mutex_death);
	free(philo->table->forks);
	free(philo->threads);
	free(philo);
	
}

int main(int        ac, char **av)
{
	t_table    table;
	t_philo     *philos;
	if (check_args(ac))
		return (1);
	if (parsing_args(av,&table))
		return (1);
	philos = malloc(sizeof(t_philo) * table.nph);
	if (!philos)
		put_errro("malloc failed\n");
	init_philosophers(philos, &table);
	start_similation(philos);
	wait_philosphers(philos);
	destroy_all_mutexes(philos);
	return (0);
}