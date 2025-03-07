/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:23:34 by llaakson          #+#    #+#             */
/*   Updated: 2025/03/01 21:11:12 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	philo_usleep(long time, t_philo *philo)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		pthread_mutex_lock(&philo->table->death_mutex);
		if (philo->table->dead == 1)
		{
			pthread_mutex_unlock(&philo->table->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->table->death_mutex);
		if (usleep(500) != 0)
			printf("Error: usleep failed\n");
	}
	return (0);
}

long	get_time(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) != 0)
		printf("Error: gettimeofday failed\n");
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	philo_printf(char *str, int name, long time, t_table *table)
{
	pthread_mutex_lock(&table->death_mutex);
	if (table->dead == 0)
	{
		pthread_mutex_lock(&table->print_mutex);
		printf("%zu %d %s\n", time, name, str);
		pthread_mutex_unlock(&table->print_mutex);
	}
	pthread_mutex_unlock(&table->death_mutex);
	return ;
}
