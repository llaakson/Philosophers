#include "philo.h"

void	destroy_threads(pthread_mutex_t *forks, char **argv)
{
	int	i;

	i = 0;
	while (i <= ft_atoi(argv[1]))
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
