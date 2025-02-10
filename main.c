#include "philo.h"

int create_threads(t_ms *ms, t_philosopher *pp)
{
	int i;

	i = 0;
	while (i < pp->philos[0].number_of_philosophers) 
	{
		pthread_create(&pp->philos[i].thread, NULL, &philosopher, &pp->philos[i]);
		//printf("%d is threading\n", pp->philos[i].name);
		i++;
	}
	i = 0;
	while (i < ms->number_of_philosophers)
	{
		pthread_join(pp->philos[i].thread, NULL);
		i++;
	}
	return (0);
}

int init_philo(t_ms *ms, char **argv)
{
	ms->number_of_philosophers = ft_atoi(argv[1]);
	ms->time_to_die = ft_atoi(argv[2]);
	ms->time_to_eat = ft_atoi(argv[3]);
	ms->time_to_sleep = ft_atoi(argv[4]);
	ms->number_of_meals = ft_atoi(argv[5]);
	//printf("Init_philo\n");
	return (ms->time_to_die);
}

int init_philosophers(t_ms *ms, pthread_mutex_t *forks, char **argv)
{	
	int i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{	
		ms[i].name = i + 1;
		if (i == 0)
			ms[i].fork_left = &forks[ft_atoi(argv[1])];
		else
			ms[i].fork_left = &forks[i - 1];
		ms[i].fork_right = &forks[i];
		if (i % 2)
		{
			ms[i].fork_left = &forks[i];
			ms[i].fork_right = &forks[i - 1];
		}
		init_philo(&ms[i], argv);
		ms[i].start = get_time();
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
	t_ms ms[200];
	t_philosopher philo;
	philo.philos = ms;
	pthread_mutex_t forks[200];

	if (argc <= 4 || argc >= 7)
	{
		write(2, "Error ac!\n", 10);
		return (1);
	}
	init_forks(forks, argv);
	init_philosophers(ms, forks, argv);
	create_threads(ms, &philo);
	destroy_threads(forks, argv);
	printf("Works\n");
	return (0);
}
