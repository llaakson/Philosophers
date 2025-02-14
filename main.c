#include "philo.h"

int create_threads(t_philosopher *pp)
{
	int i;

	i = 0;
	pthread_create(&pp->dead_check, NULL, &monitor, pp);
	while (i < pp->number_of_philosophers) 
	{
		pthread_create(&pp->ms[i].thread, NULL, &philosopher, &pp->ms[i]);
		//printf("%d is threading\n", pp->philos[i].name);
		i++;
	}
	i = 0;
	while (i < pp->number_of_philosophers)
	{
		pthread_join(pp->ms[i].thread, NULL);
		i++;
	}
	if (pthread_join(pp->dead_check, NULL) == 1)
		printf("AAA\n");
	return (0);
}

int init_philo(t_philosopher *ms, char **argv, int argc)
{
	ms->number_of_philosophers = ft_atoi(argv[1]);
	ms->time_to_die = ft_atoi(argv[2]);
	ms->time_to_eat = ft_atoi(argv[3]);
	ms->time_to_sleep = ft_atoi(argv[4]);
	ms->number_of_meals = 0;
	if (argc == 6)
		ms->number_of_meals = ft_atoi(argv[5]);
	ms->dead = 0;
	ms->start = get_time() + 1000;
	pthread_mutex_init(&ms->print_mutex, NULL);
	pthread_mutex_init(&ms->meal_mutex, NULL);
	pthread_mutex_init(&ms->death_mutex, NULL);
	return (ms->time_to_die);
}

int init_philosophers(t_philosopher *pp, pthread_mutex_t *forks)
{	
	int i;

	i = 0;
	pp->ms = malloc(sizeof(t_ms) * pp->number_of_philosophers);
	while (i < pp->number_of_philosophers)
	{	
		pp->ms[i].name = i + 1;
		if (i == 0)
			pp->ms[i].fork_left = &forks[pp->number_of_philosophers];
		else
			pp->ms[i].fork_left = &forks[i - 1];
		pp->ms[i].fork_right = &forks[i];
		if (i % 2)
		{
			pp->ms[i].fork_left = &forks[i];
			pp->ms[i].fork_right = &forks[i - 1];
		}
		pp->ms[i].table = pp;
		pp->ms[i].meals = 0;
		pp->ms[i].last_meal = pp->start;
		i++;
	}
	return (0);
}

int init_forks(pthread_mutex_t *forks, char **argv)
{
	int	i;

	i = 0;
	while (i <= ft_atoi(argv[1]))
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (0);
	
}
int main(int argc, char **argv)
{
	t_philosopher table;
	pthread_mutex_t forks[200];

	if (argc <= 4 || argc >= 7)
	{
		write(2, "Error ac!\n", 10);
		return (1);
	}
	init_philo(&table, argv, argc);
	init_forks(forks, argv);
	init_philosophers(&table, forks);
	create_threads(&table);
	destroy_threads(forks, argv);
	printf("Works\n");
	return (0);
}
