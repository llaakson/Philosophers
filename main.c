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
	return (0);
}

int init_philosophers(t_philosopher *pp)
{	
	int i;

	i = 0;
	pp->ms = malloc(sizeof(t_ms) * pp->number_of_philosophers);
	if (pp->ms == NULL)
	{
		printf("Error: fork malloc failed\n");
		return (1);
	}
	while (i < pp->number_of_philosophers)
	{	
		pp->ms[i].name = i + 1;
		if (i % 2 == 0)
		{
			if (i == 0)
				pp->ms[i].fork_left = &pp->forks[pp->number_of_philosophers - 1];
			else
				pp->ms[i].fork_left = &pp->forks[i - 1];
			pp->ms[i].fork_right = &pp->forks[i];
		}
		else
		{
			pp->ms[i].fork_left = &pp->forks[i - 1];
			pp->ms[i].fork_right = &pp->forks[i];
		}
		pp->ms[i].table = pp;
		pp->ms[i].meals = 0;
		pp->ms[i].last_meal = pp->start;
		i++;
	}
	return (0);
}

int init_forks(t_philosopher *pp)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&pp->print_mutex, NULL) != 0)
	{
		printf("Error: mutex init failed\n");
		return (1);
	}
	if (pthread_mutex_init(&pp->meal_mutex, NULL) != 0)
	{
		printf("Error: mutex init failed\n");
		pthread_mutex_destroy(&pp->print_mutex);
		return (1);
	}
	if (pthread_mutex_init(&pp->death_mutex, NULL) != 0)
	{
		printf("Error: mutex init failed\n");
		pthread_mutex_destroy(&pp->meal_mutex);
		pthread_mutex_destroy(&pp->print_mutex);
		return (1);
	}
	pp->forks = malloc(sizeof(pthread_mutex_t) * pp->number_of_philosophers);
	if (pp->forks == NULL)
	{
		printf("Error: fork malloc failed\n");
		return (1);
	}
	while (i < pp->number_of_philosophers)
	{
		pthread_mutex_init(&pp->forks[i], NULL);
		i++;
	}
	return (0);
	
}
int main(int argc, char **argv)
{
	t_philosopher table;

	if (argc <= 4 || argc >= 7)
	{
		write(2, "Error ac!\n", 10);
		return (1);
	}
	if (init_philo(&table, argv, argc))
		return (1);
	if (init_forks(&table))
		return (1);
	if (init_philosophers(&table))
	{
		destroy_threads(&table);
		return (1);
	}
	create_threads(&table);
	destroy_threads(&table);
	printf("Works\n");
	return (0);
}
