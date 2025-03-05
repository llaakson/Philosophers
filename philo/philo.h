/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaakson <llaakson@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:26:31 by llaakson          #+#    #+#             */
/*   Updated: 2025/03/05 23:54:00 by llaakson         ###   ########.fr       */
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
	struct s_philo	*philo;
	int				end;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				dead;
	int				number_of_philosophers;
	int				number_of_meals;
	long			start;
	pthread_mutex_t	*forks;
	pthread_t		dead_check;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
}	t_table;

typedef struct s_philo {
	int				name;
	int				meals;
	long			next_meal;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_table			*table;
}	t_philo;

int		ft_atoi(const char *str);
long	get_time(void);
void	*philosopher(void *ptr);
void	destroy_threads(t_table *table);
void	*ft_table(void *ptr);
int		check_input(int argc, char **argv);
void	philo_printf(char *str, int name, long time, t_table *table);
long	ft_long_atoi(const char *str);
long	philo_usleep(long time, t_philo *philo);
int		create_threads(t_table *table);
void	free_philoforks(t_table *table);
void	philo_one(t_philo *philo);
int		init_philo_mealmutex(t_table *table, int i);

#endif
