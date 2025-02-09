#include "philo.h"

pthread_mutex_t mutex;

void	philo_think(t_ms *ms)
{
	size_t time;

	time = get_time() - ms->start;
	printf("%ld %d is thinking\n", time, ms->name);
	//usleep(ms->time_to_think * 1000);
}

void	philo_sleep(t_ms *ms)
{
	size_t time;

	time = get_time() - ms->start;
	printf("%ld %d is sleeping\n", time, ms->name);
	usleep(ms->time_to_sleep * 1000);
}

void philo_eat(t_ms *ms)
{
	size_t time;
	
	pthread_mutex_lock(ms->fork_left);
	pthread_mutex_lock(ms->fork_right);
	time = get_time() - ms->start;
	printf("%ld %d is eating\n", time, ms->name);
	usleep(ms->time_to_eat * 1000);
	pthread_mutex_unlock(ms->fork_left);
	pthread_mutex_lock(ms->fork_right);
}

void	*philosopher(void *ptr)
{
	t_ms *ms;

	ms = (t_ms *)ptr;
	//printf("Created thread name %d\n", ms->name);
	while (ms->number_of_meals != 0)
	{
		philo_eat(ms);
		philo_sleep(ms);
		//philo_think(ms);
		ms->number_of_meals -= 1;
	}
	return (NULL);
}

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
	printf("Init_philo\n");
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
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&mutex, NULL);
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
	printf("Works\n");
	return (0);
}
