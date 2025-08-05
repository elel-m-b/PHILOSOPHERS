/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-m-b <elel-m-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:08:04 by elel-m-b          #+#    #+#             */
/*   Updated: 2025/08/04 13:08:28 by elel-m-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	destroy_all_mutexes(t_table *table)
{
	int	i = 0;

	while (i < table->nph)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->mutex_print);
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
    destroy_all_mutexes(philos->table);
    return (0);
}