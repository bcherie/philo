#include "philosophers.h"

void	ft_check_args(t_all *args, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		if (i == 0)
			i++;
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) != 0)
				args->digit = 0;
			else
				args->digit = 1;
			if (args->digit != 1)
				j++;
			else
				break ;
		}
		if (args->digit != 1)
			i++;
		else
			break ;
	}
}

void	ft_fill_args(t_all *args, int argc, char **argv)
{
	if (args->digit == 0)
	{
		if (argc == 5 || argc == 6)
		{
			if (argc == 6)
			{
				args->eat_times = ft_atoi(argv[5]);
				if (args->eat_times == 0)
					args->eat_times = -1;
			}
			args->n_phil = ft_atoi(argv[1]);
			args->t_die = ft_atoi(argv[2]);
			args->t_eat = ft_atoi(argv[3]);
			args->t_sleep = ft_atoi(argv[4]);
			if (args->n_phil < 1 || args->t_die < 1 || args->t_eat < 1 \
				|| args->t_sleep < 1 || args->eat_times < 0)
				ft_errors();
		}
		else
			ft_errors();
	}
	else
		ft_errors();
}
