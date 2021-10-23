#include "philosophers.h"

void	ft_init(t_all *args)
{
	args->n_phil = 0;
	args->t_die = 0;
	args->t_eat = 0;
	args->t_sleep = 0;
	args->eat_times = 0;
	args->flag_die = 0;
	args->start = 0;
	args->digit = 0;
}

void	ft_init_mutex(t_all *args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	args->phil = (t_philosoph *)calloc(args->n_phil, sizeof(t_philosoph));
	args->forks = (pthread_mutex_t *)calloc(args->n_phil, \
		sizeof(pthread_mutex_t));
	if(!args->phil || !args->forks)
	{
		if(!args->forks)
			free(args->phil);
		if(!args->phil)
			free(args->forks);
		free(args);
		exit(0);
	}
	while (j < args->n_phil)
	{
		pthread_mutex_init(&args->forks[j], NULL);
		j++;
	}
	args->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if(!args->print)
	{
		free(args->forks);
		free(args->phil_tread);
		free(args);
		exit(0);
	}
	pthread_mutex_init(args->print, NULL);
	while (i < args->n_phil)
	{
		args->phil[i].id = i;
		args->phil[i].phil_ar = args;
		args->phil[i].l_fork = &args->forks[i];
		args->phil[i].r_fork = &args->forks[(i + 1) % args->n_phil];
		i++;
	}
}
