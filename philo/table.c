/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 05:45:38 by llaakson          #+#    #+#             */
/*   Updated: 2025/03/03 17:34:44 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_meals(t_table *table, int i, int check)
{
	while (i < table->number_of_philosophers)
	{
		pthread_mutex_lock(&table->philo[i].meal_mutex);
		if (table->philo[i].meals >= table->number_of_meals)
		{
			check = 1;
		}
		else
		{
			check = 0;
			pthread_mutex_unlock(&table->philo[i].meal_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->philo[i].meal_mutex);
		i++;
	}
	if (check == 1)
	{
		pthread_mutex_lock(&table->death_mutex);
		table->dead = 1;
		pthread_mutex_unlock(&table->death_mutex);
	}
	return (check);
}

static int	check_pulse(t_table *table, int i)
{
	while (i < table->number_of_philosophers)
	{
		pthread_mutex_lock(&table->philo[i].meal_mutex);
		if ((get_time() - table->philo[i].last_meal) > table->time_to_die)
		{
			pthread_mutex_unlock(&table->philo[i].meal_mutex);
			pthread_mutex_lock(&table->death_mutex);
			table->dead = 1;
			pthread_mutex_unlock(&table->death_mutex);
			pthread_mutex_lock(&table->print_mutex);
			printf("%zu %d died\n",
				(get_time() - table->start), table->philo[i].name);
			pthread_mutex_unlock(&table->print_mutex);
			return (1);
		}
		pthread_mutex_unlock(&table->philo[i].meal_mutex);
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
		if (check_pulse(table, 0))
			return (NULL);
		if (table->number_of_meals != 0)
			if (check_meals(table, 0, 0))
				return (NULL);
	}
	return (NULL);
}
