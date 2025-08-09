/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-m-b <elel-m-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:07:46 by elel-m-b          #+#    #+#             */
/*   Updated: 2025/08/09 18:09:35 by elel-m-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     ft_numberlen(char *s)
{
    int     i;
    i = 0;
    while (s[i])
        i++;
    return (i);
}

void        put_errro(char *err)
{
    write (2, err, ft_numberlen(err));
}

int     check_args(int ac)
{
    if (ac != 6 && ac != 5)
    {
        put_errro("Error\n");
        return (1);
    }
    return (0);
}

int	ft_atoll(char	*number)
{
	int	i;
	int	signe;
	int	res;

	i = 0;
	signe = 1;
	res = 0;
    while ((number) && ((number[i] == ' ') || (number[i] >= 9 && number[i] <= 13)))
    {
        i++;
        if (number[i] == '-')
        {
            signe = -1;
            i++;
        }
    }
	if (number[i] == '+')
		i++;
	while (number[i])
	{
        if (number[i] < '0' || number[i] > '9')
        {
            put_errro("Error\n");
            return (0);
        }
		res = res * 10 + (number[i] - '0');
		i++;
	}
    // printf ("the res * signe is |%d|\n", res * signe);
	return (res * signe);
}

//./philo 199 600 200 300