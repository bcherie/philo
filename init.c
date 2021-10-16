#include "philosophers.h"

void ft_init(t_all *args)
{
	args->n_phil = 0;
	args->t_die = 0;
	args->t_eat = 0;
	args->t_sleep = 0;
	args->eat_times = 0;
	args->flag_die = 0;
	args->start = 0;
	// args->print = (pthread_mutex_t*)calloc(args->n_phil, sizeof(pthread_mutex_t));
	// pthread_mutex_init(args->print, NULL);

}

t_philosoph *init_philo(t_all *args)
{
//////


/////
	t_philosoph *phil = NULL;
	int i;
	int j;

	i = 0;
	j = 0;
	phil = (t_philosoph *)calloc(args->n_phil, sizeof(t_philosoph));
	phil->eaters = (pthread_mutex_t*)calloc(args->n_phil, sizeof(pthread_mutex_t));

	phil->death = (pthread_mutex_t*)calloc(args->n_phil, sizeof(pthread_mutex_t));
	while (j < args->n_phil)
	{
		pthread_mutex_init(&phil->death[j], NULL);
		j++;
	}
	j = 0;
	while (j < args->n_phil)
	{
		pthread_mutex_init(&phil->eaters[j], NULL);
		j++;
	}

	args->print = (pthread_mutex_t*)calloc(args->n_phil, sizeof(pthread_mutex_t));
	pthread_mutex_init(args->print, NULL);


	while (i < args->n_phil)
	{
		phil[i].id = i;
		phil[i].args = args;

		phil[i].l_fork = phil->eaters[i];
		phil[i].r_fork = phil->eaters[(i + 1) % args->n_phil];
		phil[i].print = args->print;
		i++;
	}
	// phil->left = (args->p_id + args->n_phil - 1) % args->n_phil;
	// phil->right = (args->p_id + 1) % args->n_phil;
	return(phil);
}
