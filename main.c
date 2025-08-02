#include "philo.h"



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
    return (0);
}