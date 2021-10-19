#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int n;
	int i;
	int sym;
	int k;

	sym = 1;
	i = 0;
	n = 0;
	k = 0;
	if (str[i] == '\0')
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		sym = (str[i++] == '-') ? -1 : 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = 10 * n + (str[i] - '0');
		i++;
		k++;
	}
	while (k > 19)
		return ((sym == -1) ? 0 : -1);
	return (n * sym);
}

// int	ft_atoi(const char *str)
// {
// 	int	res;
// 	int	sign;
// 	int	i;

// 	res = 0;
// 	sign = 1;
// 	i = 0;
// 	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
// 	{
// 		i++;
// 	}
// 	if (str[i] == 45 || str[i] == 43)
// 	{
// 		if (str[i] == 45)
// 		{
// 			sign = -1;
// 		}
// 		i++;
// 	}
// 	while (str[i] >= 48 && str[i] <= 57)
// 	{
// 		res = res * 10 + str[i] - 48;
// 		i++;
// 	}
// 	return ((int)(res * sign));
// }


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

void my_usleep(t_philosoph *phil)
{
	unsigned long tmp;

	tmp = check_time() - phil->phil_ar->t_sleep;
	usleep(tmp);
}

void	ft_usleep(useconds_t time)
{
	unsigned long long	t;

	t = check_time();
	while (check_time() - t < time)
		usleep(50);
}


void	*ft_memset(void *dest, int c, size_t n)
{
	char *b;

	b = (char*)dest;
	while (n-- > 0)
		*b++ = c;
	return (dest);
}

int ft_check_eat(t_all *args)
{
	int i;

	i = 0;
	while (i < args->n_phil)
	{
		if(args->phil->countEat > args->eat_times)
			break ;
		i++;
	}
	return (0);
}

