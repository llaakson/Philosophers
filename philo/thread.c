/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:23:16 by llaakson          #+#    #+#             */
/*   Updated: 2025/03/06 00:05:53 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo_mealmutex(t_table *table, int i)
{
	if (pthread_mutex_init(&table->philo[i].meal_mutex, NULL) != 0)
	{
		while (--i >= 0)
			pthread_mutex_destroy(&table->philo[i].meal_mutex);
		i = table->number_of_philosophers;
		while (--i >= 0)
			pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->print_mutex);
		pthread_mutex_destroy(&table->death_mutex);
		printf("Error: mutex init failed\n");
		free_philoforks(table);
		return (1);
	}
	return (0);
}

void	philo_one(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(philo->fork_right);
	time = get_time() - philo->table->start;
	philo_printf("has taken a fork", philo->name, time, philo->table);
	philo_usleep(philo->table->time_to_die, philo);
	pthread_mutex_unlock(philo->fork_right);
}

static int	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
			printf("Error: Failed to join thread\n");
		i++;
	}
	if (pthread_join(table->dead_check, NULL) != 0)
		printf("Error: Failed to join thread\n");
	return (0);
}

static int	create_philo_threads(t_table *table, int i)
{
	while (++i < table->number_of_philosophers)
	{
		if (pthread_create(&table->philo[i].thread,
				NULL, &philosopher, &table->philo[i]) != 0)
		{
			pthread_mutex_lock(&table->death_mutex);
			table->dead = 1;
			pthread_mutex_unlock(&table->death_mutex);
			while (--i >= 0)
				if (pthread_join(table->philo[i].thread, NULL) != 0)
					printf("Error: Failed to join thread\n");
			printf("Error: Failed to create threads\n");
			return (1);
		}
	}
	return (0);
}

int	create_threads(t_table *table)
{
	int	i;

	if (create_philo_threads(table, -1))
		return (1);
	i = table->number_of_philosophers;
	if (pthread_create(&table->dead_check, NULL, &ft_table, table) != 0)
	{
		pthread_mutex_lock(&table->death_mutex);
		table->dead = 1;
		pthread_mutex_unlock(&table->death_mutex);
		while (--i >= 0)
			if (pthread_join(table->philo[i].thread, NULL) != 0)
				printf("Error: Failed to join thread\n");
		printf("Error: Failed to create threads\n");
		return (1);
	}
	join_threads(table);
	return (0);
}
