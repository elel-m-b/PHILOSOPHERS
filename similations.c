#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
typedef     struct      s_table
{
    int     nph;
    int     td;
    int     te;
    int     ts;
}t_table;

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
        put_errro("Invalid number of argument\n");
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
    while (number[i] == ' ' || (number[i] >= 9 && number[i] <= 13))
        i++;
	if (number[i] == '-')
	{
		signe = -1;
		i++;
	}
	else if (number[i] == '+')
		i++;
	while (number[i])
	{
        if (number[i] < '0' || number[i] > '9')
        {
            put_errro("Invalid parametre\n");
            return (0);
        }
		res = res * 10 + (number[i] - '0');
		i++;
	}
	return (res * signe);
}

int     parsing_args(char **av, t_table *table)
{
    table->nph = ft_atoll(av[1]);
    table->td = ft_atoll(av[2]);
    table->te = ft_atoll(av[3]);
    table->ts = ft_atoll(av[4]);
    if (table->nph == 0 || table->td < 0 || table->te < 0 || table->ts < 0)
    {
        put_errro ("Invalid argument\n");
        return (1);
    }
    return (0);
}

int main(int        ac, char **av)
{
    t_table    table;
    if (check_args(ac))
        return (1);
    if (parsing_args(av,&table))
        return (1);
    return (0);
}