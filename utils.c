/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:23:34 by llaakson          #+#    #+#             */
/*   Updated: 2025/02/19 18:41:37 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_usleep(size_t time, t_ms *ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		if (ms->table->dead == 1)
			break ;
		usleep(100);
	}
	return (0);
}

size_t	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	philo_printf(char *str, int name, size_t time, t_philosopher *table)
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
