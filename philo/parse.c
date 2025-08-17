/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-m-b <elel-m-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:07:57 by elel-m-b          #+#    #+#             */
/*   Updated: 2025/08/17 11:08:35 by elel-m-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parsing_args(char *argv[], t_table *table)
{
	table->nph = ft_atoll(argv[1]);
	table->td = ft_atoll(argv[2]);
	table->te = ft_atoll(argv[3]);
	table->ts = ft_atoll(argv[4]);
	table->number_of_meals = -1;
	if (table->nph < 0 || table->nph > 200)
		return (put_error("Invalid argument"), 1);
	if (argv[5])
	{
		table->number_of_meals = ft_atoll(argv[5]);
		if (table->number_of_meals < 0)
			return (put_error("Invalid number of meals"), -1);
		if (!table->number_of_meals)
			return (1);
	}
	if (table->td < 0 || table->te < 0
		|| table->ts < 0 || table->nph < 0)
		return (put_error("Invalid argument"), 1);
	return (0);
}
