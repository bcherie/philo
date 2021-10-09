#include "philosophers.h"
int* state = NULL;

void ft_sleep(t_philosoph *new_one)
{

	//while (new_one->args->t_sleep)
		usleep(new_one->args->t_sleep * 1000);
}


void print_status(t_philosoph *new_one, char *print)
{

	printf("%lu Philo %d %s\n", (check_time() - new_one->args->start), \
			new_one->id, print);
}

void ft_think(t_philosoph *new_one)
{
	// printf("%lu Pholosoph thinks\n", tmp->start - check_time());
	// usleep(50);
	// return (1);
	// int time = rand() % new_one->args->t_eat;
	printf("%lu Philosopher #%d is thinking...\n", check_time() - new_one->args->start, new_one->id + 1);
	// sleep(time);
}

// int ft_eating(t_philosoph *new_one, t_all *tmp)
// {
// 	(void)tmp;
// 	if((tmp->p_id % 2) == 0)
// 	{
// 		pthread_mutex_lock(&new_one->r_fork);
// 		printf("takes r_fork\n");
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(&new_one->l_fork);
// 		printf("takes r_fork\n");
// 	}
// 	// print_status(new_one);

// 	pthread_mutex_unlock(&new_one->r_fork);
// 	pthread_mutex_unlock(&new_one->l_fork);
// 	return (2);
// }

void ft_eat(t_philosoph *new_one)
{
	// int time = rand() % new_one->args->t_eat;
	unsigned long time = new_one->args->t_eat * 1000;
	printf("%lu Philosopher #%d is eating...\n", check_time() - new_one->args->start, new_one->id + 1);
	usleep(time);
    // printf("%lu Philosopher #%d stopped eating...\n", check_time() - new_one->args->start, new_one->id + 1);
}

void test(t_philosoph *new_one)
{
	int i;

	i = new_one->id;
	if (state[i] == HUNGRY && state[i - 1] != EATING && state[i + 1] != EATING)
	{
		state[i] = EATING; //меняем статус, что наш i-й философ поел
		pthread_mutex_unlock(&new_one->eaters[i]); //филосов начал есть, поэтому инкрементируем семафор, чтобы философа не заблокировали соседи
    }
}

void ft_take_fork(t_philosoph *new_one)
{
	//mutex
	// state = (unsigned int *)malloc(sizeof(unsigned int));
	pthread_mutex_lock(&new_one->r_fork);
	pthread_mutex_lock(&new_one->l_fork);
	//pthread_mutex_lock(new_one->eaters);
	state[new_one->id] = HUNGRY;
	ft_eat(new_one);
	//test(new_one); // попытка взять две вилки
	pthread_mutex_unlock(&new_one->r_fork);
	pthread_mutex_unlock(&new_one->l_fork);
	//pthread_mutex_lock(&new_one->eaters[new_one->id]);
}

void ft_put_fork(t_philosoph *new_one)
{
	pthread_mutex_lock(&new_one->r_fork);
	pthread_mutex_lock(&new_one->l_fork);
	state[new_one->id] = THINKING;
	test(new_one);
	// test(new_one);
	pthread_mutex_unlock(&new_one->r_fork);
	pthread_mutex_unlock(&new_one->l_fork);
}

//work for each phil
void *tread(void *new_one)
{
	while (1)
	{
		ft_think(new_one);
		// ft_eating(new_one, tmp);
		ft_take_fork(new_one);

		// t_philosoph *tmp = new_one;
		//ft_eat(new_one);
		// printf("Philosopher #%d is sleeping...\n", tmp->id + 1);
		// printf("Philosopher #%d is thinking...\n", tmp->id + 1);
		//ft_put_fork(new_one);
		// new_one->start_eat = tmp->start - check_time();
		print_status(new_one, "is sleeping");
		ft_sleep(new_one);

		// print_status(new_one, "is thinking");
	}

	// printf("%d\n", phil->die);
	// printf("allright");
	// exit(0);
}

t_philosoph *init_philo(t_all *args)
{
	t_philosoph *phil = NULL;
	int i;
	int j;

	i = 0;
	j = 0;
	state = (int *)calloc(args->n_phil, sizeof(int));
	ft_memset(state, 0, args->n_phil);
	phil = (t_philosoph *)calloc(args->n_phil, sizeof(t_philosoph));
	phil->eaters = (pthread_mutex_t*)calloc(args->n_phil, sizeof(pthread_mutex_t));
	while (j < args->n_phil)
	{
		pthread_mutex_init(&phil->eaters[j], NULL);
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
		// phil[i].l_fork = phil->eaters[i];

		phil[i].l_fork = phil->eaters[i];

		//phil[i].l_fork = phil->eaters[(i + args->n_phil - 1) % args->n_phil];
		// phil[i].r_fork = phil->eaters[i];

		phil[i].r_fork = phil->eaters[(i + 1) % args->n_phil];
		i++;
	}
	// phil->left = (args->p_id + args->n_phil - 1) % args->n_phil;
	// phil->right = (args->p_id + 1) % args->n_phil;
	return(phil);
}

void ft_check_philos(t_all *args)
{
	int num;
	int result;
	t_philosoph *new_one;
	// pthread_mutex_t *phil = NULL;


	num = 0;
	result = 0;
	// phil = malloc(sizeof(pthread_mutex_t));
	// pthread_mutex_init(phil, NULL);
	pthread_t *phil_treads;

	phil_treads = malloc(sizeof(pthread_t) * args->n_phil);
	new_one = init_philo(args);
	if(!phil_treads)
		printf("Malloc error\n");
	while (num < args->n_phil)
	{
		args->start = check_time(); //start simulation
		result = pthread_create(&phil_treads[num], NULL, tread, &new_one[num]);
		usleep(1000);
		num += 2;
	}
	num = 1;
	while (num < args->n_phil)
	{
		args->start = check_time(); //start simulation
		result = pthread_create(&phil_treads[num], NULL, tread, &new_one[num]);
		usleep(1000);
		num += 2;
	}
	num = 0;
	while (num < args->n_phil)
	{
		pthread_detach(phil_treads[num]);
		num++;
	}
	//pthread_join(phil_treads[num], NULL);
}
void ft_init(t_all *args)
{
	args->n_phil = 0;
	args->t_die = 0;
	args->t_eat = 0;
	args->t_sleep = 0;
	args->eat_times = 0;

}

int main(int argc, char **argv)
{
	t_all *args;
	// pthread_t id;
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
	// printf("%d\n", digit);
	// printf("%s\n", argv[1]);
	if (digit == 0)
	{
		if (argc == 5 || argc == 6)
		{
			if (argc == 6)
				args->eat_times = ft_atoi(argv[5]);
			args->n_phil = ft_atoi(argv[1]); // make atoi
			args->t_die = ft_atoi(argv[2]);
			args->t_eat = ft_atoi(argv[3]);
			args->t_sleep = ft_atoi(argv[4]);
		}
		else
			printf("error args\n");
	}
	else
		printf("you put no digit\n");

	// }
	// printf("%s, %s, %s, %s\n", args.n_phil, args.t_die, args.t_eat, args.t_sleep);
	ft_check_philos(args);
	while(1)
	{
		usleep(50);

	}
	//pthread_create(&id, NULL, tread, NULL);
	return (0);
}
