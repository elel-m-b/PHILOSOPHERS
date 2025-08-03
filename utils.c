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
    while ((number[i] == ' ') || (number[i] >= 9 && number[i] <= 13))
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
	return (res * signe);
}
void	philog(t_philo *philo, const char *action)
{
	long long	interval;
	long long	start;
	int			id;

	interval = 0;
	id = philo->id;
	start = philo->table->start_time;
	interval = time_now() - start;
	if (philo->table->is_death)
		return ;
	pthread_mutex_lock(&(philo->table->mutex_print));
	if (!philo->table->is_death)
		printf("%lld %d %s\n", interval, id, action);
	if (*action == 'd')
		philo->table->is_death = 1;
	pthread_mutex_unlock(&(philo->table->mutex_print));
}