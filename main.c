#include "philosophers.h"

void	stop_tread(t_all *args)
{
	int	i;

	i = 0;
	while (i < args->n_phil)
	{
		pthread_detach(args->phil_tread[i]);
		i++;
	}
	pthread_mutex_destroy(args->print);
	pthread_mutex_destroy(args->forks);
	free(args->forks);
	free(args->phil_tread);
	free(args);
	exit(0);
}

void	check_death(t_all *args)
{
	unsigned long	t;
	int				i;
	int				kol_vo_sitih;

	i = 0;
	t = 0;
	kol_vo_sitih = 0;
	while (i < args->n_phil)
	{
		t = check_time() - args->phil[i].last_eat;
		if (args->eat_times && args->phil[i].countEat >= args->eat_times)
		{
			kol_vo_sitih++;
			if (kol_vo_sitih == args->n_phil)
				stop_tread(args);
		}
		if (t > args->t_die)
		{
			args->flag_die = 1;
			ft_print_status(&args->phil[i], "dies");
			stop_tread(args);
		}
		i++;
	}
}

void	*tread(void *phil)
{
	t_philosoph	*tmp;

	tmp = (t_philosoph *) phil;
	tmp->last_eat = check_time();
	while (1)
	{
		ft_print_status(tmp, "thinks");
		ft_take_fork(tmp);
		tmp->countEat++;
		ft_print_status(tmp, "sleeps");
		ft_wait(tmp->phil_ar->t_sleep);
	}
	return (NULL);
}

void	ft_pthread_create(t_all *args)
{
	int	num;

	num = 0;
	args->phil_tread = malloc(sizeof(pthread_t) * args->n_phil);
	if (!args->phil_tread)
	{
		printf("Malloc error\n");
		exit(0);
	}
	while (num < args->n_phil)
	{
		args->start = check_time();
		pthread_create(&args->phil_tread[num], NULL, tread, &args->phil[num]);
		usleep(25);
		num += 2;
	}
	usleep(50);
	num = 1;
	while (num < args->n_phil)
	{
		args->start = check_time();
		pthread_create(&args->phil_tread[num], NULL, tread, &args->phil[num]);
		usleep(25);
		num += 2;
	}
}

int	main(int argc, char **argv)
{
	t_all	*args;

	args = malloc(sizeof(t_all));
	if(!args)
		return(-1);
	ft_init(args);
	if (argc == 5 || argc == 6)
		ft_check_args(args, argv);
	else
	{
		printf("Error: wrong args\n");
		return (-1);
	}
	ft_fill_args(args, argc, argv);
	ft_init_mutex(args);
	ft_pthread_create(args);
	while (1)
	{
		check_death(args);
		if (args->flag_die == 1)
			break ;
		else
			usleep(100);
	}
	return (0);
}
