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

static int	join_threads(t_philosopher *pp)
{
	int	i;

	i = 0;
	while (i < pp->number_of_philosophers)
	{
		if (pthread_join(pp->ms[i].thread, NULL) != 0)
		{
			while (--i >= 0)
				pthread_detach(pp->ms[i].thread);
			pthread_detach(pp->dead_check);
			printf("Error: Failed to join thread\n");
			return (1);
		}
		i++;
	}
	if (pthread_join(pp->dead_check, NULL) != 0)
	{
		printf("Error: Failed to join thread\n");
		return (1);
	}
	return (0);
}

int	create_threads(t_philosopher *pp)
{
	int	i;

	i = -1;
	if (pthread_create(&pp->dead_check, NULL, &monitor, pp) != 0)
		return (1);
	while (++i < pp->number_of_philosophers)
	{
		if (pthread_create(&pp->ms[i].thread,
				NULL, &philosopher, &pp->ms[i]) != 0)
		{
			while (--i >= 0)
				pthread_detach(pp->ms[i].thread);
			pthread_detach(pp->dead_check);
			printf("Error: Failed to create threads\n");
			return (1);
		}
	}
	if (join_threads(pp))
		return (1);
	return (0);
}
