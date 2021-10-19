#include "philosophers.h"

void ft_check_args(t_all *args, char **argv)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	j = 0;
	res = 0;
	while (argv[i])
	{
		// printf("%s\n", argv[i]);
		if (i == 0)
			i++;
		j = 0;
		while (argv[i][j])
		{
			if((res = ft_isdigit(argv[i][j])) != 0)
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

void ft_fill_args(t_all *args, int argc, char **argv)
{
	if (args->digit == 0)
	{
		if (argc == 5 || argc == 6)
		{
			if (argc == 6)
				args->eat_times = ft_atoi(argv[5]);
			// printf("%d\n", args->eat_times);
			args->n_phil = ft_atoi(argv[1]); // make atoi
			args->t_die = ft_atoi(argv[2]);
			args->t_eat = ft_atoi(argv[3]);
			args->t_sleep = ft_atoi(argv[4]);
			// printf("%d\n", args->n_phil);
			// printf("%lu\n", args->t_die);
			// printf("%lu\n", args->t_eat);
			// printf("%lu\n", args->t_sleep);
			// printf("%lu\n", args->eat_times);
			if (args->n_phil < 1 || args->t_die < 1 || args->t_eat < 1 || args->t_sleep < 1)
				printf("Error: args aren't digits\n");
		}
		else
			printf("error args\n");
	}
	else
		printf("you put no digit\n");

}
