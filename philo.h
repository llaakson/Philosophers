/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:26:31 by llaakson          #+#    #+#             */
/*   Updated: 2025/02/19 13:47:40 by llaakson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_table {
	struct s_philo		*philo;
	int				end;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				dead;
	int				number_of_philosophers;
	int				number_of_meals;
	size_t			start;
	pthread_mutex_t	*forks;
	pthread_t		dead_check;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
}	t_table;

typedef struct s_philo {
	int				name;
	int				meals;
	size_t			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_table	*table;
}	t_philo;

int		ft_atoi(const char *str);
size_t	get_time(void);
void	*philosopher(void *ptr);
void	destroy_threads(t_table *pp);
void	*monitor(void *ptr);
int		check_input(int argc, char **argv);
void	philo_printf(char *str, int name, size_t time, t_table *table);
long	ft_long_atoi(const char *str);
size_t	ft_usleep(size_t time, t_philo *philo);
int		create_threads(t_table *pp);
void	free_philoforks(t_table *pp);

#endif
