#include "philosophers.h"


void stop_tread(t_philosoph *new_one, pthread_t *phil_treads)
{
	int i;

	i = 0;
	while (i < new_one->args->n_phil)
	{
		pthread_detach(phil_treads[i]);
		i++;
	}
	pthread_mutex_destroy(new_one->death);
	pthread_mutex_destroy(new_one->args->print);
	pthread_mutex_destroy(new_one->eaters);
	free(new_one->eaters);
	free(phil_treads);
}

void check_death(t_philosoph *new_one)
{
	unsigned long t;
	int i;

	i = 0;

	while (i < new_one->args->n_phil)
	{
		t = check_time() - new_one[i].args->last_eat;
		if(t > new_one[i].args->t_die)
		{
			new_one->args->flag_die = 1;
			// if (!new_one->status_die)
			ft_print_status(&new_one[i], "dies");
			//printf("%lu Philosopher #%d dies.\n", check_time() - new_one->args->start, new_one->id + 1);
			// pthread_mutex_lock(&new_one->death[new_one->id]);
			// pthread_mutex_lock(new_one[new_one->id].print);
			// new_one->status_die = &i + 1;
			return;
		}
		i++;
	}
	// while (i < new_one->args->n_phil)
	// {
	// 	check_death(new_one);
	// 	i++;
	// }

}

// void ft_sleep(t_philosoph *new_one)
// {
// 	usleep(check_time() - new_one->args->t_sleep);
// }


void ft_take_fork(t_philosoph *new_one)
{
	pthread_mutex_lock(new_one->r_fork);
	pthread_mutex_lock(new_one->l_fork);
	// ft_eat(new_one);
	ft_print_status(new_one, "takes forks");
	ft_print_status(new_one, "is eating");
	usleep(new_one->args->t_eat);
	printf("\neat: %lu\n", new_one->args->t_eat);
	new_one->args->last_eat = check_time();
	// printf("last_eat: %lu\n", new_one->args->last_eat);
	if (new_one->args->flag_die != 1)
	{
		pthread_mutex_unlock(new_one->r_fork);
		pthread_mutex_unlock(new_one->l_fork);
	}
}


//work for each phil
void *tread(void *new_one)
{

	t_philosoph *tmp;

	tmp = (t_philosoph *)new_one;

	while (1)
	{
		ft_print_status(tmp, "thinks");
		// ft_think(new_one);
		ft_take_fork(tmp);
		ft_print_status(tmp, "is sleeping");
		usleep(tmp->args->t_sleep);
		//ft_sleep(new_one);
		// usleep(500);
	}
}


void ft_check_philos(t_all *args, t_philosoph **new_one)
{
	int num;
	int result;
	// t_philosoph *new_one;

	num = 0;
	result = 0;
	pthread_t *phil_treads;

	phil_treads = malloc(sizeof(pthread_t) * args->n_phil);
	*new_one = init_philo(args);
	if(!phil_treads)
		printf("Malloc error\n");
	// while (1)
	// {
		while (num < args->n_phil)
		{
			(*new_one)[num].args->start = check_time(); //start simulation
			(*new_one)[num].args->last_eat = (*new_one)[num].args->start;
			result = pthread_create(&phil_treads[num], NULL, tread, &(*new_one)[num]);
			usleep(25);
			num += 2;
		}
		num = 1;
		while (num < args->n_phil)
		{
			(*new_one)[num].args->start = check_time(); //start simulation
			(*new_one)[num].args->last_eat = (*new_one)[num].args->start;
			result = pthread_create(&phil_treads[num], NULL, tread, &(*new_one)[num]);
			usleep(25);
			num += 2;
		}
		// }
		// num = 0;
		// check_death(new_one);
		if((*new_one)->args->flag_die == 1)
			stop_tread(*new_one, phil_treads);
		// 	break ;
		// }
		// usleep(50);
	// }
	// while (num < args->n_phil)
	// {
	// 	pthread_detach(phil_treads[num]);
	// 	num++;
	// }
}

int main(int argc, char **argv)
{
	t_philosoph *new_one = NULL;
	t_all *args;
	int i;
	int	j;
	int digit;
	int res = 0;

	i = 0;
	j = 0;
	digit = 0;
	// new_one = malloc(sizeof(t_philosoph));
	args = malloc(sizeof(t_all));
	ft_init(args);
	while (argv[i])
	{
		// printf("%s\n", argv[i]);
		if (i == 0)
			i++;
		j = 0;
		while (argv[i][j])
		{
			if((res = ft_isdigit(argv[i][j])) != 0)
				digit = 0;
			else
				digit = 1;
			if (digit != 1)
				j++;
			else
				break ;
		}
		//вынести диджит в стуктуру
		if (digit != 1)
			i++;
		else
			break ;
	}
	// printf("%d\n", i);
	if (digit == 0)
	{
		if (argc == 5 || argc == 6)
		{
			if (argc == 6)
				args->eat_times = ft_atoi(argv[5]);
			// printf("%lu\n", args->eat_times);
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

	ft_check_philos(args, &new_one);
	//new_one = init_philo(args);
	// printf("%d\n", args->n_phil);
	// printf("%lu\n", args->t_die);
	// printf("%lu\n", args->t_eat);
	// printf("%lu\n", args->t_sleep);
	// printf("%lu\n", args->eat_times);
	while(1)
	{
		// if (new_one->args->n_phil > 1)
		// else
		// 	printf("%lu Philosopher #%d takes forks\n", check_time() - new_one->args->start, new_one->id + 1);
		// usleep(500);
		check_death(new_one);
		if (new_one->args->flag_die == 1)
			break ;
		else
			continue ;
		usleep(50);
	}
	return (0);
}
