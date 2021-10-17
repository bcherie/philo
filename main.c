#include "philosophers.h"


void stop_tread(t_all *args, pthread_t *phil_treads)
{
	int i;

	i = 0;
	while (i < args->n_phil)
	{
		pthread_detach(phil_treads[i]);
		i++;
	}
	//pthread_mutex_destroy(new_one->death);
	pthread_mutex_destroy(args->print);
	pthread_mutex_destroy(args->forks);
	free(args->forks);
	free(phil_treads);
}

void check_death(t_all *args)
{
	unsigned long t;
	int i;

	i = 0;
	t = 0;
	while (i < args->n_phil)
	{
		t = check_time() - args->phil[i].last_eat;
		if(t > args->t_die && args->phil[i].last_eat != args->phil[i].phil_ar->start)
		{
			args->flag_die = 1;
			// if (!new_one->status_die)
			ft_print_status(&args->phil[i], "dies");
			//printf("%lu Philosopher #%d dies.\n", check_time() - new_one->args->start, new_one->id + 1);
			// pthread_mutex_lock(&new_one->death[new_one->id]);
			// pthread_mutex_lock(args->phil[i].phil_ar->print);
			// new_one->status_die = &i + 1;
			// return;
			break ;
		}
		i++;
	}
}


//work for each phil
void *tread(void *phil)
{
	t_philosoph *tmp;

	tmp = (t_philosoph *) phil;
	tmp->last_eat = check_time();
	while (1)
	{
		ft_print_status(tmp, "thinks");
		ft_take_fork(tmp);
		tmp->countEat++;
		//(args->phil[i].countEat > args->eat_times)
		// tmp->last_eat = check_time();
		ft_print_status(tmp, "is sleeping");
		ft_usleep(tmp->phil_ar->t_sleep);
		// ft_usleep(tmp->phil_ar->t_sleep);
	}
}


void ft_pthread_create(t_all *args)
{
	int	num;
	int	result;

	pthread_t *phil_tread;
	num = 0;
	result = 0;
	phil_tread = malloc(sizeof(pthread_t) * args->n_phil);
	// args->phil->phil_ar = args;
	if(!phil_tread)
		printf("Malloc error\n");
	while (num < args->n_phil)
	{
		args->start = check_time(); //start simulation
		// args->phil[num].last_eat = args->start;
		result = pthread_create(&phil_tread[num], NULL, tread, &args->phil[num]);
		usleep(25);
		num += 2;
	}
	num = 1;
	while (num < args->n_phil)
	{
		args->start = check_time(); //start simulation
		// args->phil[num].last_eat = args->start;
		result = pthread_create(&phil_tread[num], NULL, tread, &args->phil[num]);
		usleep(25);
		num += 2;
	}
	if(args->flag_die == 1)
		stop_tread(args, phil_tread);
}

int main(int argc, char **argv)
{
	t_all *args;
	int i;
	int	j;
	int digit;

	i = 0;
	j = 0;
	digit = 0;
	// new_one = malloc(sizeof(t_philosoph));
	args = malloc(sizeof(t_all));
	ft_init(args);
	ft_check_args(args, argv);
	ft_fill_args(args, argc, argv);
	ft_init_mutex(args);
	ft_pthread_create(args);
	while(1)
	{
		check_death(args);
		if (args->flag_die == 1)
			break ;
		else
			continue ;
		usleep(100);
	}
	return (0);
}
