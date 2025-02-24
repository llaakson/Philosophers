/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:23:16 by llaakson          #+#    #+#             */
/*   Updated: 2025/02/19 20:32:48 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
		{
			while (--i >= 0)
				pthread_detach(table->philo[i].thread);
			pthread_detach(table->dead_check);
			printf("Error: Failed to join thread\n");
			return (1);
		}
		i++;
	}
	if (pthread_join(table->dead_check, NULL) != 0)
	{
		printf("Error: Failed to join thread\n");
		return (1);
	}
	return (0);
}

int	create_threads(t_table *table)
{
	int	i;

	i = -1;
	if (pthread_create(&table->dead_check, NULL, &monitor, table) != 0)
		return (1);
	while (++i < table->number_of_philosophers)
	{
		if (pthread_create(&table->philo[i].thread,
				NULL, &philosopher, &table->philo[i]) != 0)
		{
			while (--i >= 0)
				pthread_detach(table->philo[i].thread);
			pthread_detach(table->dead_check);
			printf("Error: Failed to create threads\n");
			return (1);
		}
	}
	if (join_threads(table))
		return (1);
	return (0);
}
