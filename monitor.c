/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 05:45:38 by llaakson          #+#    #+#             */
/*   Updated: 2025/02/19 16:01:05 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals(t_philosopher *pp, int i, int check)
{
	while (i < pp->number_of_philosophers)
	{
		pthread_mutex_lock(&pp->meal_mutex);
		if (pp->ms[i].meals >= pp->number_of_meals)
		{
			check = 1;
		}
		else
		{
			check = 0;
			pthread_mutex_unlock(&pp->meal_mutex);
			break ;
		}
		pthread_mutex_unlock(&pp->meal_mutex);
		i++;
	}
	pthread_mutex_lock(&pp->death_mutex);
	if (check == 1)
		pp->dead = 1;
	pthread_mutex_unlock(&pp->death_mutex);
	return (pp->dead);
}

int	check_pulse(t_philosopher *pp, int i, size_t time)
{
	while (i < pp->number_of_philosophers)
	{
		pthread_mutex_lock(&pp->meal_mutex);
		time = get_time() - pp->ms[i].last_meal;
		pthread_mutex_unlock(&pp->meal_mutex);
		pthread_mutex_lock(&pp->death_mutex);
		if (time > pp->time_to_die)
		{
			pp->dead = 1;
			pthread_mutex_unlock(&pp->death_mutex);
			pthread_mutex_lock(&pp->print_mutex);
			printf("%zu %d died\n", time, pp->ms[i].name);
			pthread_mutex_unlock(&pp->print_mutex);
			return (1);
		}
		pthread_mutex_unlock(&pp->death_mutex);
		i++;
	}
	return (0);
}

void	*monitor(void *ptr)
{
	t_philosopher	*pp;

	pp = (t_philosopher *)ptr;
	while (get_time() < pp->start)
		usleep(100);
	while (1)
	{
		if (check_pulse(pp, 0, 0))
			return (NULL);
		if (pp->number_of_meals != 0)
			if (check_meals(pp, 0, 0))
				return (NULL);
	}
	return (NULL);
}
