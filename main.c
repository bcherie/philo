#include "philosophers.h"


void print_status(t_philosoph *new_one, char *print)
{

	printf("%lu Philo %d %s\n", (check_time() - new_one->args->start), \
			new_one->id, print);
}

void stop_tread(t_philosoph *new_one, pthread_t *phil_treads)
{
	int i;

	i = 0;
	while (i < new_one->args->n_phil)
	{
		pthread_detach(phil_treads[i]);
		i++;
	}
	// pthread_mutex_destroy(phil_treads[i]);
}

void check_death(t_philosoph *new_one)
{
	unsigned long t;
	int i;

	i = 0;
	t = check_time() - new_one->last_eat;

	if(t > new_one[new_one->id].args->t_die)
	{
		new_one->args->flag_die = 1;
		pthread_mutex_lock(&new_one->death[new_one->id]);
		printf("%lu Philosopher #%d dies...\n", check_time() - new_one->args->start, new_one->id + 1);
	}
	while (i < new_one->args->n_phil)
	{
		check_death(new_one);
		i++;
	}

}

int ft_eat(t_philosoph *new_one)
{
	if(new_one->args->flag_die == 0)
	{
		pthread_mutex_lock(&new_one->l_fork);
		pthread_mutex_lock(&new_one->r_fork);
		printf("%lu Philosopher #%d is eating...\n", check_time() - new_one->args->start, new_one->id + 1);
	}
	// if(new_one->args->flag_die == 0)
	// 	{
	// 		pthread_mutex_lock(&new_one->l_fork);
	// 		printf("%lu Philosopher #%d takes l_fork...\n", check_time() - new_one->args->start, new_one->id + 1);
	// 		pthread_mutex_lock(&new_one->r_fork);
	// printf("%lu Philosopher #%d takes r_fork...\n", check_time() - new_one->args->start, new_one->id + 1);
	// printf("%lu Philosopher #%d is eating...\n", check_time() - new_one->args->start, new_one->id + 1);
	my_usleep(new_one->args->t_eat);
	new_one->last_eat = check_time();

	// usleep(time);
	pthread_mutex_unlock(&new_one->r_fork);
	pthread_mutex_unlock(&new_one->l_fork);
	return (2);
}

void ft_sleep(t_philosoph *new_one)
{

	while (new_one->args->t_sleep)
		usleep(new_one->args->t_sleep * 1000);
}

//work for each phil
void *tread(void *new_one)
{
	t_philosoph *tmp;

	tmp = new_one;
	while (1)
	{
		// if(tmp->id % 2 == 0)
		// 	my_usleep(100);
		ft_eat(new_one);
		// printf("Philosopher #%d is sleeping...\n", tmp->id + 1);
		// printf("Philosopher #%d is thinking...\n", tmp->id + 1);
		// ft_put_fork(new_one);
		// new_one->start_eat = tmp->start - check_time();
		print_status(new_one, "is sleeping");
		ft_sleep(new_one);
		print_status(new_one, "is thinking");
		// usleep(50);
	}
}


void ft_check_philos(t_all *args)
{
	int num;
	int result;
	t_philosoph *new_one;


	num = 0;
	result = 0;
	pthread_t *phil_treads = malloc(sizeof(pthread_t) * args->n_phil);
	new_one = init_philo(args);
	if(!phil_treads)
		printf("Malloc error\n");
	while (num < args->n_phil)
	{
		args->start = check_time(); //start simulation
		// printf("секунды:% ld\nnmicro секунд:% d\n", current_time.tv_sec, current_time.tv_usec);
		result = pthread_create(&phil_treads[num], NULL, tread, &new_one[num]);
		usleep(100);
		num++;
	}
	// check_death(new_one);
	// stop_tread(new_one, phil_treads);
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
	args = malloc(sizeof(t_all));
	ft_init(args);
	// printf("%d\n", argc);
	// if(argc != 6 && argc != 5)
	// 	printf("Error argc\n");
	// else
	// {
	// printf("%s\n", argv[i]);
	argv[i] = argv[1];
	while (argv[i])
	{
		// printf("%s\n", argv[i]);
		while (argv[i][j])
		{
			if(ft_isdigit(argv[i][j]))
				digit = 0;
			else
				digit = 1;
			j++;
		}
		i++;
	}
	if(digit == 0)
	{
		if(argc == 5 || argc == 6)
		{
			if(argc == 6)
				args->eat_times = ft_atoi(argv[5]);
			args->n_phil = ft_atoi(argv[1]);
			args->t_die = ft_atoi(argv[2]);
			args->t_eat = ft_atoi(argv[3]);
			args->t_sleep = ft_atoi(argv[4]);
			if (args->n_phil < 1 || args->t_die < 1 || args->t_eat < 1 || args->t_sleep < 1)
				printf("Error: args aren't digits\n");
		}
		else
			printf("error args\n");
	}
	else
		printf("you put no digit\n");
	// printf("%s, %s, %s, %s\n", args.n_phil, args.t_die, args.t_eat, args.t_sleep);
	ft_check_philos(args);
	//pthread_create(&id, NULL, tread, NULL);
	return (0);
}
