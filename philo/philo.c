/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:22:54 by llaakson          #+#    #+#             */
/*   Updated: 2025/03/05 23:51:37 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_think(t_philo *philo)
{
	long	time;

	time = get_time() - philo->table->start;
	philo_printf("is thinking", philo->name, time, philo->table);
}

static void	philo_sleep(t_philo *philo)
{
	long	time;

	time = get_time() - philo->table->start;
	philo_printf("is sleeping", philo->name, time, philo->table);
	philo_usleep(philo->table->time_to_sleep, philo);
}

static void	ft_forks(t_philo *philo)
{
	if (philo->name % 2 != 0)
	{
		pthread_mutex_lock(philo->fork_right);
		philo_printf("has taken a fork", philo->name,
			(get_time() - philo->table->start), philo->table);
		pthread_mutex_lock(philo->fork_left);
		philo_printf("has taken a fork", philo->name,
			(get_time() - philo->table->start), philo->table);
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		philo_printf("has taken a fork", philo->name,
			(get_time() - philo->table->start), philo->table);
		pthread_mutex_lock(philo->fork_right);
		philo_printf("has taken a fork", philo->name,
			(get_time() - philo->table->start), philo->table);
	}
}

static void	philo_eat(t_philo *philo)
{
	long	delay;

	delay = philo->next_meal - get_time();
	if (philo->table->number_of_philosophers % 2 != 0 && delay > 0)
		philo_usleep(delay, philo);
	ft_forks(philo);
	philo_printf("is eating", philo->name,
		(get_time() - philo->table->start), philo->table);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->next_meal = philo->last_meal + (philo->table->time_to_eat * 2) + 1;
	pthread_mutex_unlock(&philo->meal_mutex);
	philo_usleep(philo->table->time_to_eat, philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals += 1;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	*philosopher(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (get_time() < philo->table->start)
		usleep(100);
	if (philo->table->number_of_philosophers == 1)
	{
		philo_one(philo);
		return (NULL);
	}
	if (philo->name % 2 != 0)
		philo_sleep(philo);
	pthread_mutex_lock(&philo->table->death_mutex);
	while (philo->table->dead == 0)
	{
		pthread_mutex_unlock(&philo->table->death_mutex);
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
		pthread_mutex_lock(&philo->table->death_mutex);
	}
	pthread_mutex_unlock(&philo->table->death_mutex);
	return (NULL);
}
