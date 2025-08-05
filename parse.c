/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-m-b <elel-m-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:07:57 by elel-m-b          #+#    #+#             */
/*   Updated: 2025/08/04 13:07:58 by elel-m-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int     parsing_args(char **av, t_table *table)
{
    table->nph = ft_atoll(av[1]);
    table->td = ft_atoll(av[2]);
    table->te = ft_atoll(av[3]);
    table->ts = ft_atoll(av[4]);
    table->is_death = 1;
    if (table->nph <= 0 || table->td < 0 || table->te < 0 || table->ts < 0)
    {
        put_errro ("Error\n");
        return (1);
    }
    return (0);
}