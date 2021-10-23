#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
	{
		i++;
	}
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
		{
			sign = -1;
		}
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return ((int)(res * sign));
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

unsigned long	check_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_wait(useconds_t t)
{
	unsigned long long	time;

	time = check_time();
	while (check_time() - time < t)
		usleep(25);
}

void	ft_errors(void)
{
	printf("Error arguments\n");
	exit(0);
}
