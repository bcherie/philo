#include "philosophers.h"

void ft_init(t_all *args)
{
	args->n_phil = 0;
	args->t_die = 0;
	args->t_eat = 0;
	args->t_sleep = 0;
	args->eat_times = 0;
	args->flag_die = 0;

}

t_philosoph *init_philo(t_all *args)
{
	t_philosoph *phil = NULL;
	int i;
	int j;

	i = 0;
	j = 0;
	phil = (t_philosoph *)calloc(args->n_phil, sizeof(t_philosoph));
	// phil->flag_die = 0;
	while (j < args->n_phil)
	{
		phil->eaters = (pthread_mutex_t*)calloc(args->n_phil, sizeof(pthread_mutex_t));
		j++;
	}
	j = 0;
	while (j < args->n_phil)
	{
		phil->death = (pthread_mutex_t*)calloc(args->n_phil, sizeof(pthread_mutex_t));
		j++;
	}

	while (i < args->n_phil)
	{
		phil[i].id = i;
		phil[i].args = args;
		// phil[i].left = (phil[i].id + args->n_phil - 1) % args->n_phil;
		// phil[i].right = (phil[i].id + 1) % args->n_phil;
		// phil[i].left = phil->eaters[(i + args->n_phil - 1) % args->n_phil];
		// phil[i].right = phil->eaters[(i + 1) % args->n_phil];

		phil[i].l_fork = phil->eaters[i];
		phil[i].l_fork = phil->eaters[(i + args->n_phil - 1) % args->n_phil];
		phil[i].r_fork = phil->eaters[i];
		phil[i].r_fork = phil->eaters[(i + 1) % args->n_phil];
		i++;
	}
	// phil->left = (args->p_id + args->n_phil - 1) % args->n_phil;
	// phil->right = (args->p_id + 1) % args->n_phil;
	return(phil);
}
