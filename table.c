/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 05:45:38 by llaakson          #+#    #+#             */
/*   Updated: 2025/02/25 16:07:34 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_meals(t_table *table, int i, int check)
{
	while (i < table->number_of_philosophers)
	{
		pthread_mutex_lock(&table->meal_mutex);
		if (table->philo[i].meals >= table->number_of_meals)
		{
			check = 1;
		}
		else
		{
			check = 0;
			pthread_mutex_unlock(&table->meal_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->meal_mutex);
		i++;
	}
	pthread_mutex_lock(&table->death_mutex);
	if (check == 1)
		table->dead = 1;
	pthread_mutex_unlock(&table->death_mutex);
	return (check);
}

static int	check_pulse(t_table *table, int i, size_t time)
{
	while (i < table->number_of_philosophers)
	{
		pthread_mutex_lock(&table->meal_mutex);
		time = get_time() - table->philo[i].last_meal;
		pthread_mutex_unlock(&table->meal_mutex);
		pthread_mutex_lock(&table->death_mutex);
		if (time > table->time_to_die)
		{
			table->dead = 1;
			pthread_mutex_unlock(&table->death_mutex);
			pthread_mutex_lock(&table->print_mutex);
			printf("%zu %d died\n", time, table->philo[i].name);
			pthread_mutex_unlock(&table->print_mutex);
			return (1);
		}
		pthread_mutex_unlock(&table->death_mutex);
		i++;
	}
	return (0);
}

void	*ft_table(void *ptr)
{
	t_table	*table;

	table = (t_table *)ptr;
	while (get_time() < table->start)
		usleep(100);
	while (1)
	{
		if (check_pulse(table, 0, 0))
			return (NULL);
		if (table->number_of_meals != 0)
			if (check_meals(table, 0, 0))
				return (NULL);
	}
	return (NULL);
}
