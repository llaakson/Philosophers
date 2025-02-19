/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:37:52 by llaakson          #+#    #+#             */
/*   Updated: 2025/02/19 20:08:46 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philosophers(t_philosopher *pp, int i)
{
	while (i < pp->number_of_philosophers)
	{
		pp->ms[i].name = i + 1;
		if (i % 2 == 0)
		{
			if (i == 0)
				pp->ms[i].fork_left
					= &pp->forks[pp->number_of_philosophers - 1];
			else
				pp->ms[i].fork_left = &pp->forks[i - 1];
			pp->ms[i].fork_right = &pp->forks[i];
		}
		else
		{
			pp->ms[i].fork_left = &pp->forks[i - 1];
			pp->ms[i].fork_right = &pp->forks[i];
		}
		pp->ms[i].table = pp;
		pp->ms[i].meals = 0;
		pp->ms[i].last_meal = pp->start;
		i++;
	}
	return (0);
}

int	init_mutexes(t_philosopher *pp)
{
	if (pthread_mutex_init(&pp->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&pp->meal_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&pp->print_mutex);
		return (1);
	}
	if (pthread_mutex_init(&pp->death_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&pp->meal_mutex);
		pthread_mutex_destroy(&pp->print_mutex);
		return (1);
	}
	return (0);
}

int	init_forks(t_philosopher *pp, int i)
{
	if (init_mutexes(pp))
		return (1);
	pp->forks = malloc(sizeof(pthread_mutex_t) * pp->number_of_philosophers);
	if (pp->forks == NULL)
	{
		printf("Error: fork malloc failed\n");
		return (1);
	}
	while (i < pp->number_of_philosophers)
	{
		if (pthread_mutex_init(&pp->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&pp->forks[i]);
			pthread_mutex_destroy(&pp->meal_mutex);
			pthread_mutex_destroy(&pp->print_mutex);
			pthread_mutex_destroy(&pp->death_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_philo(t_philosopher *table, char **argv, int argc)
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
	table->ms = malloc(sizeof(t_ms) * table->number_of_philosophers);
	if (table->ms == NULL)
	{
		printf("Error: fork malloc failed\n");
		return (1);
	}
	if (init_forks(table, 0))
	{
		printf("Error: mutex init failed\n");
		free_philoforks(table);
		return (1);
	}
	init_philosophers(table, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philosopher	table;

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
	if (init_philo(&table, argv, argc))
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
