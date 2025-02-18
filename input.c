#include "philo.h"

long	ft_long_atoi(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	if (*str == '-' || *str == '+' )
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		result = result * 10 + *str++ - 48;
	return (result * sign);
}

static int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_input(int argc, char **argv)
{
	int	i;
	long	n;

	i = 1;
	while (i < argc)
	{
		if (!(ft_isnumber(argv[i])))
			return (1);
		n = ft_long_atoi(argv[i]);
		if (!(n > 0 && n <= INT_MAX))
			return (1);
		i++;
	}
	return (0);
}
