/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-m-b <elel-m-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:07:46 by elel-m-b          #+#    #+#             */
/*   Updated: 2025/08/17 21:19:58 by elel-m-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(long interval, t_philo *philo)
{
	long	now;

	now = time_now();
	while (time_now() - now < interval)
	{
		if (check_died(philo))
			return (1);
		usleep(300);
	}
	return (0);
}

int	ft_numberlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	put_error(char *err)
{
	write(2, err, ft_numberlen(err));
}

int	check_args(int ac)
{
	if (ac != 6 && ac != 5)
	{
		put_error("Invalid argumnet\n");
		return (1);
	}
	return (0);
}

long	ft_atoll(char *str)
{
	long	num;
	int		sign;

	while (*str == ' ' || *str == '\t')
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	if (!*str)
		return (-1);
	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str++ - '0';
		if (num * sign > INT_MAX || num * sign < INT_MIN)
			return (-1);
	}
	while (*str == ' ' || *str == '\t')
		str++;
	if (sign * num < 0 || *str)
		return (-1);
	return (sign * num);
}
