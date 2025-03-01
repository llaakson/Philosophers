/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:22:54 by llaakson          #+#    #+#             */
/*   Updated: 2025/02/25 13:35:34 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_think(t_philo *philo)
{
	size_t	time;

	time = get_time() - philo->table->start;
	philo_printf("is thinking", philo->name, time, philo->table);
}

static void	philo_sleep(t_philo *philo)
{
	size_t	time;

	time = get_time() - philo->table->start;
	philo_printf("is sleeping", philo->name, time, philo->table);
	philo_usleep(philo->table->time_to_sleep, philo);
}

static void	philo_eat(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(philo->fork_right);
	time = get_time() - philo->table->start;
	philo_printf("has taken a fork", philo->name, time, philo->table);
	pthread_mutex_lock(philo->fork_left);
	time = get_time() - philo->table->start;
	philo_printf("has taken a fork", philo->name, time, philo->table);
	philo_printf("is eating", philo->name, time, philo->table);
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->table->meal_mutex);
	philo_usleep(philo->table->time_to_eat, philo);
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->meals += 1;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

static void	philo_one(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(philo->fork_right);
	time = get_time() - philo->table->start;
	philo_printf("has taken a fork", philo->name, time, philo->table);
	philo_usleep(philo->table->time_to_die, philo);
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
