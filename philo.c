#include <pthread.h>
#include <stdio.h>
#include <unistd.h> 
#include <signal.h>
#include <stdlib.h>

typedef struct s_table
{
    int             number_of_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    pthread_mutex_t *forks;
    pthread_t       *threads;
} t_table;

typedef struct s_philo
{
    int         id;
    t_table     *table;
    int         left_fork;
    int         right_fork;
} t_philo;

void print_error_and_exit()
{
    printf("Error in argument\n");
    exit(1);
}

int ft_atoi(char *str)
{
    int i = 0;
    int res = 0;
    
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            print_error_and_exit();
        i++;
    }
    
    i = 0;
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return (res);
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    printf("Philosopher %d is thinking\n", philo->id);
    pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
    printf("Philosopher %d has taken left fork %d\n", philo->id, philo->left_fork);
    pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
    printf("Philosopher %d has taken right fork %d\n", philo->id, philo->right_fork);
    printf("Philosopher %d is eating\n", philo->id);
    usleep(philo->table->time_to_eat * 1000);

    pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
    pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
    printf("Philosopher %d is sleeping\n", philo->id);
    
    return NULL;
}

void init_table(t_table *table)
{
    int i;
    table->threads = malloc(sizeof(pthread_t) * table->number_of_philo);
    table->forks = malloc(sizeof(pthread_mutex_t) * table->number_of_philo);
    
    if (!table->threads || !table->forks)
        print_error_and_exit();
    i = 0;
    while (i < table->number_of_philo)
    {
        if (pthread_mutex_init(&table->forks[i], NULL) != 0)
            print_error_and_exit();
        i++;
    }
}

void ft_create_philosophers(t_table *table)
{
    int i;
    t_philo *philos;
    
    philos = malloc(sizeof(t_philo) * table->number_of_philo);
    if (!philos)
        print_error_and_exit();
    
    i = 0;
    while (i < table->number_of_philo)
    {
        philos[i].id = i;
        philos[i].table = table;
        philos[i].left_fork = i;
        philos[i].right_fork = (i + 1) % table->number_of_philo;
        pthread_create(&table->threads[i], NULL, philo_routine, &philos[i]);
        i++;
    }
    i = 0;
    while (i < table->number_of_philo)
    {
        pthread_join(table->threads[i], NULL);
        i++;
    }
}

void cleanup_table(t_table *table)
{
    int i;

    i = 0;
    while (i < table->number_of_philo)
    {
        pthread_mutex_destroy(&table->forks[i]);
        i++;
    }
    free(table->forks);
    free(table->threads);
}

int main(int ac, char **av)
{
    t_table table;
    
    if (ac == 5)
    {
        table.number_of_philo = ft_atoi(av[1]);
        table.time_to_die = ft_atoi(av[2]);
        table.time_to_eat = ft_atoi(av[3]);
        table.time_to_sleep = ft_atoi(av[4]);
        
        printf("Number of philosophers: %d\n", table.number_of_philo);
        printf("Time to die: %d ms\n", table.time_to_die);
        printf("Time to eat: %d ms\n", table.time_to_eat);
        printf("Time to sleep: %d ms\n", table.time_to_sleep);
    }
    else 
        print_error_and_exit();
    
    init_table(&table);
    ft_create_philosophers(&table);
    cleanup_table(&table);
    
    return (0);
}