/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-m-b <elel-m-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:46:09 by elel-m-b          #+#    #+#             */
/*   Updated: 2025/08/07 17:52:27 by elel-m-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_now(void)
{
    struct timeval	tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
void	philog(t_philo *philo, const char *message)
{
	long	interval;
	long	start;
	int			id;

	interval = 0;
	id = philo->id;
	start = philo->table->start_time;
	interval = time_now() - start;
	pthread_mutex_lock(&(philo->table->mutex_print));
	if (!philo->table->is_death)
		printf("%ld %d %s\n", interval, id, message);
	if (*message == 'd')
    {
	    //pthread_mutex_lock(&(philo->table->mutex_meals));
		philo->table->is_death = 1;
	    //pthread_mutex_unlock(&(philo->table->mutex_meals));
    }
	pthread_mutex_unlock(&(philo->table->mutex_print));
}

void ft_eat(t_philo *philo)
{
	t_table	*table;
	table = philo->table;
	pthread_mutex_lock(philo->left_fork);
    philog(philo, TAKE_FORK);
    // if (philo->table->nph == 1)
    // {
    //     usleep(philo->table->td * 1000);
    //     philog(philo, DEAD);
    //     return ;
    // }
	pthread_mutex_lock(philo->right_fork);
    philog(philo, TAKE_FORK);
	philog(philo, EATING);
    philo->last_meal_time = time_now();
    usleep(table->te * 1000); 
    pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
void    ft_sleep(t_philo *philo)
{
    philog(philo, SLEEPPING);
    usleep(philo->table->ts * 1000);
}
void    ft_think(t_philo *philo)
{
    philog(philo, THINKING);
    // if (philo->id % 2 != 0)
    //     usleep(500);
    // if (philo->table->te * 3 >= philo->table->td)
    //     usleep(philo->table->te * 1000);
    // else
    //     //usleep (1000);
    // if (philo->table->nph % 2)
    //     usleep((philo->table->te - philo->table->ts + 200) * 1000);
}
void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_table     *table;
    table = philo->table;
    if (table->nph == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        philog(philo, TAKE_FORK);
        usleep(philo->table->td * 1000);
        philog(philo, DEAD);
        pthread_mutex_unlock(philo->left_fork);
        return NULL;
    }
    if (philo->id % 2 == 0)
        usleep(1000);
    while (!table->is_death)
    {
        ft_think(philo);
        ft_eat(philo);
        ft_sleep(philo);
    }
    return (NULL);
}
void init_philosophers(t_philo *philos, t_table *table)
{
    int     i;
    i = 0;
    int     n_philo = table->nph;
    philos->threads = malloc(sizeof(pthread_t) * table->nph);
    table->forks = malloc(sizeof(pthread_mutex_t) * table->nph);
    table->start_time = time_now();
    // printf ("the start time are %lld\n", table->start_time);
    pthread_mutex_init(&(table->mutex_print), NULL);
    pthread_mutex_init(&(table->mutex_meals), NULL);
    while (i < table->nph)
    {
        pthread_mutex_init(&(table->forks[i]), NULL);
        philos[i].table = table;
        philos[i].id = i + 1;
        philos->table->is_death = 0;
		philos[i].left_fork= &(table->forks[i]);
        philos[i].right_fork = &(table->forks[(i + 1) % n_philo]);
        philos[i].last_meal_time = time_now();
        i++;
    }
}
int monitor(t_philo *philos)
{
    int i;
    while (1)
    {
        i = 0;
        while (i < philos->table->nph)
        {
            if (time_now() - philos[i].last_meal_time >= philos[i].table->td)
            {
                philog(&philos[i], DEAD);
                philos->table->is_death = 1;
                return 1;
            }
            i++;
        }
    }
}
void    wait_philosphers(t_philo *philos)
{
    int     i;
    i = 0;
    while (i < philos->table->nph)
    {
        pthread_join(philos->threads[i], NULL);
        i++;
    }
}
void        start_similation(t_philo *philos)
{
    int     i;
    i = 0;
    while (i < philos->table->nph)
    {
        pthread_create(&philos->threads[i], NULL, routine, &philos[i]);
        i++;
    }
    monitor(philos);
    return ;
}
// ./philo 199 300 100 80
//./philo 199 599 200 200