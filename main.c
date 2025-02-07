#include "philo.h"

void	*philosopher(void *ms)
{
	struct s_ms *msp = (struct s_ms*)ms;
	usleep(msp->time_to_die);
	size_t time;
	printf("Time to die %ld \n", time = get_time());
	return (NULL);
}

int create_threads(t_ms *ms)
{
	pthread_t philo[200];
	int i;

	i = 0;
	while (i < ms->number_of_philosophers) 
	{
		pthread_create(philo + i, NULL, &philosopher, (void *) ms);
		i++;
	}
	i = 0;
	while (i < ms->number_of_philosophers)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
	return (0);
}

int init_philosophers(t_ms *ms, pthread_mutex_t *forks)
{	
	int i;

	i = 0;
	while (i < ms->number_of_philosophers)
	{	
		ms->name = i;
		ms->fork_left = forks[i];
		ms->fork_right = forks[i];
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
	printf("Time to die: %d\n", ms->time_to_die);
	return (ms->time_to_die);
}

int init_forks(pthread_mutex_t *forks, t_ms *ms)
{
	int	i;

	i = 0;
	while (i < ms->number_of_philosophers)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (0);
	
}
int main(int argc, char **argv)
{
	t_ms ms;
	//t_philosopher philo;
	pthread_mutex_t forks[200];

	if (argc < 5 || argc >= 6)
	{
		write(2, "Error ac!\n", 10);
		return (1);
	}
	init_philo(&ms, argv);
	init_forks(forks, &ms);
	init_philosophers(&ms, forks);
	create_threads(&ms);
	printf("Works\n");
	return (0);
}
