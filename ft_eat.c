#include "philosophers.h"

void ft_take_fork(t_philosoph *phil)
{
	if(phil->phil_ar->n_phil == 1)
	{
		ft_print_status(phil, "takes forks");
		ft_print_status(phil, "dead");
		exit(0);
		//stop_tread(phil, phil->threarad)
	}
	pthread_mutex_lock(phil->r_fork);
	pthread_mutex_lock(phil->l_fork);
	ft_print_status(phil, "takes forks");
	ft_print_status(phil, "is eating");
	phil->last_eat = check_time();
	// t = check_time - phil->phil_ar->t_eat;
	// usleep(t);
	// my_useat(phil);
	ft_usleep(phil->phil_ar->t_eat);
	// printf("\neat: %lu\n", args->t_eat);
	// phil->last_eat = check_time();
	// printf("last_eat: %lu\n", new_one->args->last_eat);
	if (phil->phil_ar->flag_die != 1)
	{
		pthread_mutex_unlock(phil->r_fork);
		pthread_mutex_unlock(phil->l_fork);
	}
}
