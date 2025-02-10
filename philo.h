#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_ms {
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_must_eat;
	int	number_of_meals;
	int	name;
	size_t	start;
	pthread_t thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
} t_ms;

typedef struct s_philosopher {
	t_ms	*philos;
} t_philosopher;

int     ft_atoi(const char *str);
size_t  get_time();
void    *philosopher(void *ptr);
void	destroy_threads(pthread_mutex_t *forks, char **argv);

#endif
