#include "philo.h"

int	ft_atoi(const char *str)
{
	int				sign;
	long long int	result;
	long long int	prev;

	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '-' || *str == '+' )
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		prev = result * 10 + *str++ - 48;
		if (prev / 10 != result && sign == -1)
			return (0);
		if (prev / 10 != result && sign == 1)
			return (-1);
		result = prev;
	}
	return (result * sign);
}

size_t	get_time()
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}
