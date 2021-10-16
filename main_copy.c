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
	pthread_mutex_destroy(new_one->print);
	pthread_mutex_destroy(new_one->eaters);
	free(new_one->eaters);
	free(phil_treads);
}

void check_death(t_philosoph *new_one)
{
	unsigned long t;
	int i;

	i = 0;

	t = check_time() - new_one[new_one->id].last_eat;
	new_one->status_die = (int *)malloc(sizeof(int));
	new_one->status_die = 0;
	while (i < new_one->args->n_phil)
	{
		if(t > check_time() - new_one[i].args->t_die)
		{
			new_one->args->flag_die = 1;
			if (!new_one->status_die)
				printf("%lu Philosopher #%d dies...\n", check_time() - new_one->args->start, new_one->id + 1);
			pthread_mutex_lock(&new_one->death[new_one->id]);
			pthread_mutex_lock(new_one[new_one->id].print);
			new_one->status_die = &i + 1;
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


void ft_sleep(t_philosoph *new_one)
{

	usleep(check_time() - new_one->args->t_sleep);
}


void print_status(t_philosoph *new_one, char *print)
{
	if (!new_one->status_die)
	{
		pthread_mutex_lock(new_one->print);
		printf("%lu Philo %d %s\n", (check_time() - new_one->args->start), new_one->id + 1, print);
		pthread_mutex_unlock(new_one->print);
	}
}

//объединить с предудущей
void ft_think(t_philosoph *new_one)
{
	if (!new_one->status_die)
	{
		pthread_mutex_lock(new_one->print);
		printf("%lu Philosopher #%d is thinking...\n", check_time() - new_one->args->start, new_one->id + 1);
		pthread_mutex_unlock(new_one->print);
	}
}

void ft_eat(t_philosoph *new_one)
{
	if (!new_one->status_die)
	{
		unsigned long time = new_one->args->t_eat * 1000;
		pthread_mutex_lock(new_one->print);
		printf("%lu Philosopher #%d is eating...\n", check_time() - new_one->args->start, new_one->id + 1);
		pthread_mutex_unlock(new_one->print);
		usleep(time);
	}
}

void ft_take_fork(t_philosoph *new_one)
{
	pthread_mutex_lock(&new_one->r_fork);
	pthread_mutex_lock(&new_one->l_fork);
	ft_eat(new_one);
	new_one->last_eat = check_time();
	pthread_mutex_unlock(&new_one->r_fork);
	pthread_mutex_unlock(&new_one->l_fork);
}


//work for each phil
void *tread(void *new_one)
{
	while (1)
	{
		ft_think(new_one);
		ft_take_fork(new_one);
		print_status(new_one, "is sleeping");
		ft_sleep(new_one);
		usleep(100);
	}
}


void ft_check_philos(t_all *args)
{
	int num;
	int result;
	t_philosoph *new_one;

	num = 0;
	result = 0;
	pthread_t *phil_treads;

	phil_treads = malloc(sizeof(pthread_t) * args->n_phil);
	new_one = init_philo(args);
	if(!phil_treads)
		printf("Malloc error\n");
	while (num < args->n_phil)
	{
		new_one->args->start = check_time(); //start simulation
		result = pthread_create(&phil_treads[num], NULL, tread, &new_one[num]);
		usleep(1000);
		num += 2;
	}
	num = 1;
	while (num < args->n_phil)
	{
		new_one->args->start = check_time(); //start simulation
		result = pthread_create(&phil_treads[num], NULL, tread, &new_one[num]);
		usleep(1000);
		num += 2;
	}
	// }
	// num = 0;
	check_death(new_one);
	stop_tread(new_one, phil_treads);
	// while (num < args->n_phil)
	// {
	// 	pthread_detach(phil_treads[num]);
	// 	num++;
	// }
}

int main(int argc, char **argv)
{
	t_all *args;
	int i;
	int	j;
	int digit;
	int res = 0;

	i = 0;
	j = 0;
	digit = 0;
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

	ft_check_philos(args);
	// while(1)
	// {
	// 	usleep(50);

	// }
	return (0);
}
