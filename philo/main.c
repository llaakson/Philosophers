/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:37:52 by llaakson          #+#    #+#             */
/*   Updated: 2025/03/06 00:00:13 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philo(t_table *table, int i)
{
	while (++i < table->number_of_philosophers)
	{
		table->philo[i].name = i + 1;
		if (i % 2 == 0)
		{
			if (i == 0)
				table->philo[i].fork_left
					= &table->forks[table->number_of_philosophers - 1];
			else
				table->philo[i].fork_left = &table->forks[i - 1];
			table->philo[i].fork_right = &table->forks[i];
		}
		else
		{
			table->philo[i].fork_left = &table->forks[i - 1];
			table->philo[i].fork_right = &table->forks[i];
		}
		table->philo[i].table = table;
		table->philo[i].meals = 0;
		table->philo[i].last_meal = table->start;
		table->philo[i].next_meal = table->start;
		if (init_philo_mealmutex(table, i))
			return (1);
	}
	return (0);
}

static int	init_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
	{
		printf("Error: mutex init failed\n");
		return (1);
	}
	if (pthread_mutex_init(&table->death_mutex, NULL) != 0)
	{
		printf("Error: mutex init failed\n");
		pthread_mutex_destroy(&table->print_mutex);
		return (1);
	}
	return (0);
}

static int	init_forks(t_table *table, int i)
{
	table->forks = malloc(sizeof(pthread_mutex_t)
			* table->number_of_philosophers);
	if (table->forks == NULL)
	{
		printf("Error: fork malloc failed\n");
		return (1);
	}
	if (init_mutexes(table))
		return (1);
	while (i < table->number_of_philosophers)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->forks[i]);
			pthread_mutex_destroy(&table->print_mutex);
			pthread_mutex_destroy(&table->death_mutex);
			printf("Error: mutex init failed\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_table(t_table *table, char **argv, int argc)
{
	table->number_of_philosophers = ft_long_atoi(argv[1]);
	table->time_to_die = ft_long_atoi(argv[2]);
	table->time_to_eat = ft_long_atoi(argv[3]);
	table->time_to_sleep = ft_long_atoi(argv[4]);
	table->number_of_meals = 0;
	if (argc == 6)
		table->number_of_meals = ft_long_atoi(argv[5]);
	table->dead = 0;
	table->start = get_time() + 1000;
	table->forks = NULL;
	table->philo = malloc(sizeof(t_philo) * table->number_of_philosophers);
	if (table->philo == NULL)
	{
		printf("Error: fork malloc failed\n");
		return (1);
	}
	if (init_forks(table, 0))
	{
		free_philoforks(table);
		return (1);
	}
	if (init_philo(table, -1))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc <= 4 || argc >= 7)
	{
		printf("Error: Incorrect argument count give 5 to 6 arguments\n");
		return (1);
	}
	if (check_input(argc, argv))
	{
		printf("Error: Use only positive integers\n");
		return (1);
	}
	if (init_table(&table, argv, argc))
		return (1);
	if (create_threads(&table))
	{
		destroy_threads(&table);
		free_philoforks(&table);
		return (1);
	}
	destroy_threads(&table);
	free_philoforks(&table);
	return (0);
}
