/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:28:38 by llaakson          #+#    #+#             */
/*   Updated: 2025/02/19 12:43:23 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philoforks(t_table *table)
{	
	if (table->forks)
	{
		free(table->forks);
		table->forks = NULL;
	}
	if (table->philo)
	{
		free (table->philo);
		table->philo = NULL;
	}
}

void	destroy_threads(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->death_mutex);
	while (i < table->number_of_philosophers)
	{
		pthread_mutex_destroy(&table->philo[i].meal_mutex);
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
}
