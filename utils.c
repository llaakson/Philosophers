#include "philo.h"

size_t	ft_usleep(size_t time)
{
	size_t start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(500);
	return (0);
}

size_t	get_time()
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void philo_printf(char *str, int name, size_t time, t_philosopher *table)
{
	pthread_mutex_lock(&table->death_mutex);
	if (table->dead == 0)
	{	
		pthread_mutex_unlock(&table->death_mutex);
		pthread_mutex_lock(&table->print_mutex);
		printf("%zu %d %s\n", time, name, str);
		pthread_mutex_unlock(&table->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&table->death_mutex);
	return ;
}
