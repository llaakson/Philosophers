#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_philosopher {
	struct s_ms	*ms;
	int end;
	size_t	time_to_die;
	size_t time_to_eat;
	size_t time_to_sleep;
	int dead;
	int number_of_philosophers;
	int number_of_meals;
	size_t  start;
	pthread_t dead_check;
	pthread_mutex_t print_mutex;
	pthread_mutex_t meal_mutex;
	pthread_mutex_t death_mutex;
} t_philosopher;

typedef struct s_ms {
	int	name;
	int meals;
	size_t last_meal;
	pthread_t thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_philosopher *table;
} t_ms;

int     ft_atoi(const char *str);
size_t  get_time();
void    *philosopher(void *ptr);
void	destroy_threads(pthread_mutex_t *forks, char **argv);
void    *monitor(void *ptr);
int ft_isdigit(int c);
void philo_printf(char *str, int name, size_t time, t_philosopher *table);

#endif
