#include "philosophers.h"

void	ft_print_status(t_philosoph *phil, char *status)
{
	pthread_mutex_lock(phil->phil_ar->print);
	printf("%lu Philosopher #%d %s.\n", check_time() - phil->phil_ar->start, \
		phil->id + 1, status);
	if (phil->phil_ar->flag_die != 1)
		pthread_mutex_unlock(phil->phil_ar->print);
}
