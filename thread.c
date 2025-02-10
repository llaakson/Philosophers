#include "philo.h"

void	philo_think(t_ms *ms)
{
	size_t time;

	time = get_time() - ms->start;
	printf("%ld %d is thinking\n", time, ms->name);
	usleep(1000000);
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
	time = get_time() - ms->start;
	printf("%ld %d has taken a fork\n", time, ms->name);
	pthread_mutex_lock(ms->fork_right);
	time = get_time() - ms->start;
	printf("%ld %d is eating\n", time, ms->name);
	usleep(ms->time_to_eat * 1000);
	pthread_mutex_unlock(ms->fork_right);
	pthread_mutex_unlock(ms->fork_left);
}

void	*philosopher(void *ptr)
{
	t_ms *ms;

	ms = (t_ms *)ptr;
	//printf("Created thread name %d\n", ms->name);
	if (ms->name % 2 != 0)
		philo_think(ms);
	while (ms->number_of_meals != 0)
	{
		philo_eat(ms);
		philo_sleep(ms);
		philo_think(ms);
		ms->number_of_meals -= 1;
	}
	return (NULL);
}

