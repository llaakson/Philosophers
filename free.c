/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:28:38 by llaakson          #+#    #+#             */
/*   Updated: 2025/02/15 19:30:10 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo.h"

void	destroy_threads(t_philosopher *pp)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&pp->print_mutex);
	pthread_mutex_destroy(&pp->meal_mutex);
	pthread_mutex_destroy(&pp->death_mutex);
	while (i < pp->number_of_philosophers)
	{
		pthread_mutex_destroy(&pp->forks[i]);
		i++;
	}
	free(pp->forks);
	pp->forks = NULL;
	if (pp->ms)
	{
		free (pp->ms);
		pp->ms = NULL;
	}
}
