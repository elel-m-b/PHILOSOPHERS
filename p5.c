#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


/*
    1 - understand the problem is and the diff btween threads and process and create two thread
    hanldle data race + diff between data race and race condition + understand what is deadlock
*/

/*
    2 - check_args / errors like a simple parsing
*/

/*
    3 - init strcut with valid input
*/

/*
    4 - init table with create threads and mutux with good understanding
*/

/*
    5 - similation with function routine and algorithm with handle all cases / destroy philo 
*/

/*
    6 - deep understanding of process management and cpu shedelling and all that staffs basics
*/

/*
    7 - bonus good understanding
*/

int main()
{
    
}



int	main(int argc, char *argv[])
{
	t_table	table;
	t_philo	*p;

	if (check_args(argc))
		return (1);
	if (parse_args(argv, &table))
		return (1);
	p = malloc(sizeof(t_philo) * table.philos);
	if (!p)
		return (err_w("Malloc failed"), -1);
	table.forks = malloc(sizeof(pthread_mutex_t) * table.philos);
	if (!table.forks)
		return (err_w("Malloc failed"), free(p), -1);
	if (init_philo(&table, p))
		return (1);
	if (nietzsche_party(&table))
		return (1);
	destroy_philo(&table);
}
