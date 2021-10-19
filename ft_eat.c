#include "philosophers.h"

void ft_take_fork(t_philosoph *phil)
{
	// phil->countEat++
	// if(phil->phil_ar->n_phil == 1)
	// {
	// 	ft_print_status(phil, "takes forks");
	// 	ft_print_status(phil, "dead");
	// 	exit(0);
	// 	//stop_tread(phil, phil->threarad)
	// }
	pthread_mutex_lock(phil->r_fork);
	pthread_mutex_lock(phil->l_fork);
	ft_print_status(phil, "takes forks");
	ft_print_status(phil, "is eating");
	// if (phil->countEat < phil->phil_ar->eat_times)
		// phil->countEat++;
	printf("counea %d\n", phil->countEat);
	phil->last_eat = check_time();
	ft_usleep(phil->phil_ar->t_eat);
	phil->countEat++;
	if (phil->phil_ar->flag_die != 1)
	{
		pthread_mutex_unlock(phil->r_fork);
		pthread_mutex_unlock(phil->l_fork);
	}

	// if(phil->phil_ar->flag_die == 1)
	// {
	// 	pthread_mutex_unlock(phil->r_fork);
	// 	pthread_mutex_unlock(phil->l_fork);
	// }
}
