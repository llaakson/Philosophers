/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:37:52 by llaakson          #+#    #+#             */
/*   Updated: 2025/02/15 19:37:56 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int create_threads(t_philosopher *pp)
{
	int i;

	i = 0;
	if (pthread_create(&pp->dead_check, NULL, &monitor, pp) != 0)
		return (1);
	while (i < pp->number_of_philosophers) 
	{
		if (pthread_create(&pp->ms[i].thread, NULL, &philosopher, &pp->ms[i]) != 0)
		{
			while (--i >= 0)
				pthread_detach(&pp->ms[i].thread);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < pp->number_of_philosophers)
	{
		if (pthread_join(pp->ms[i].thread, NULL) != 0)
		{
			while (--i >= 0)
				pthread_detach(&pp->ms[i].thread);
			pthread_detach(&pp->dead_check);
			return (1);
		}
		i++;
	}
	if (pthread_join(pp->dead_check, NULL) != 0)
		printf("Failed to join thread\n");
	return (0);
}

int init_philo(t_philosopher *ms, char **argv, int argc)
{
	ms->number_of_philosophers = ft_long_atoi(argv[1]);
	ms->time_to_die = ft_long_atoi(argv[2]);
	ms->time_to_eat = ft_long_atoi(argv[3]);
	ms->time_to_sleep = ft_long_atoi(argv[4]);
	ms->number_of_meals = 0;
	if (argc == 6)
		ms->number_of_meals = ft_long_atoi(argv[5]);
	ms->dead = 0;
	ms->start = get_time() + 1000;
	return (0);
}

int init_philosophers(t_philosopher *pp)
{	
	int i;

	i = 0;
	pp->ms = malloc(sizeof(t_ms) * pp->number_of_philosophers);
	if (pp->ms == NULL)
	{
		printf("Error: fork malloc failed\n");
		return (1);
	}
	while (i < pp->number_of_philosophers)
	{	
		pp->ms[i].name = i + 1;
		if (i % 2 == 0)
		{
			if (i == 0)
				pp->ms[i].fork_left = &pp->forks[pp->number_of_philosophers - 1];
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

int init_forks(t_philosopher *pp)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&pp->print_mutex, NULL) != 0)
	{
		printf("Error: mutex init failed\n");
		return (1);
	}
	if (pthread_mutex_init(&pp->meal_mutex, NULL) != 0)
	{
		printf("Error: mutex init failed\n");
		pthread_mutex_destroy(&pp->print_mutex);
		return (1);
	}
	if (pthread_mutex_init(&pp->death_mutex, NULL) != 0)
	{
		printf("Error: mutex init failed\n");
		pthread_mutex_destroy(&pp->meal_mutex);
		pthread_mutex_destroy(&pp->print_mutex);
		return (1);
	}
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
			while (i-- >= 0)
				pthread_mutex_destroy(&pp->forks[i]);
			pthread_mutex_destroy(&pp->meal_mutex);
			pthread_mutex_destroy(&pp->print_mutex);
			pthread_mutex_destroy(&pp->print_mutex);
			return (1);
		}
		i++;
	}
	return (0);
	
}
int main(int argc, char **argv)
{
	t_philosopher table;

	if (argc <= 4 || argc >= 7)
	{
		write(2, "Error ac!\n", 10);
		return (1);
	}
	if (check_input(argc, argv))
	{	
		printf("NUMBER PLZ\n");
		return (1);
	}
	if (init_philo(&table, argv, argc))
		return (1);
	if (init_forks(&table))
		return (1);
	if (init_philosophers(&table))
	{
		destroy_threads(&table);
		return (1);
	}
	if (create_threads(&table))
	{
		destroy_threads(&table);
		return (1);
	}
	destroy_threads(&table);
	printf("Works\n");
	return (0);
}
