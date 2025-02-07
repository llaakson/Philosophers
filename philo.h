#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philosopher {
	int	name;
} t_philosopher;

typedef struct s_ms {
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_must_eat;
	int	name;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	fork_right;
	t_philosopher	*philosophers;
} t_ms;

int     ft_atoi(const char *str);
size_t  get_time();

#endif
