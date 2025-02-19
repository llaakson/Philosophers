/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:22:54 by llaakson          #+#    #+#             */
/*   Updated: 2025/02/19 18:43:54 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_ms *ms)
{
	size_t	time;

	time = get_time() - ms->table->start;
	philo_printf("is thinking", ms->name, time, ms->table);
}

void	philo_sleep(t_ms *ms)
{
	size_t	time;

	time = get_time() - ms->table->start;
	philo_printf("is sleeping", ms->name, time, ms->table);
	ft_usleep(ms->table->time_to_sleep, ms);
}

void	philo_eat(t_ms *ms)
{
	size_t	time;

	pthread_mutex_lock(ms->fork_right);
	time = get_time() - ms->table->start;
	philo_printf("has taken a fork", ms->name, time, ms->table);
	pthread_mutex_lock(ms->fork_left);
	time = get_time() - ms->table->start;
	philo_printf("has taken a fork", ms->name, time, ms->table);
	philo_printf("is eating", ms->name, time, ms->table);
	pthread_mutex_lock(&ms->table->meal_mutex);
	ms->last_meal = get_time();
	ms->meals += 1;
	pthread_mutex_unlock(&ms->table->meal_mutex);
	ft_usleep(ms->table->time_to_eat, ms);
	pthread_mutex_unlock(ms->fork_left);
	pthread_mutex_unlock(ms->fork_right);
}

void	philo_one(t_ms *ms)
{
	size_t	time;

	pthread_mutex_lock(ms->fork_right);
	time = get_time() - ms->table->start;
	philo_printf("has taken a fork", ms->name, time, ms->table);
	ft_usleep(ms->table->time_to_die, ms);
	pthread_mutex_unlock(ms->fork_right);
}

void	*philosopher(void *ptr)
{
	t_ms	*ms;

	ms = (t_ms *)ptr;
	while (get_time() < ms->table->start)
		usleep(100);
	if (ms->table->number_of_philosophers == 1)
	{
		philo_one(ms);
		return (NULL);
	}
	if (ms->name % 2 != 0)
		philo_sleep(ms);
	pthread_mutex_lock(&ms->table->death_mutex);
	while (ms->table->dead == 0)
	{
		pthread_mutex_unlock(&ms->table->death_mutex);
		philo_think(ms);
		philo_eat(ms);
		philo_sleep(ms);
		pthread_mutex_lock(&ms->table->death_mutex);
	}
	pthread_mutex_unlock(&ms->table->death_mutex);
	return (NULL);
}
