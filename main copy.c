#include "philosophers.h"


void print_status(t_philosoph *new_one, char *print)
{

	printf("%lu Philo %d %s\n", (check_time() - new_one->args->start), \
			new_one->id, print);
}

unsigned int* state = NULL;

// void ft_think(t_philosoph *new_one)
// {
// 	// printf("%lu Pholosoph thinks\n", tmp->start - check_time());
// 	// usleep(50);
// 	// return (1);
// 	// int time = rand() % new_one->args->t_eat;
// 	printf("%lu Philosopher #%d is thinking...\n", check_time() - new_one->args->start, new_one->id + 1);
// 	// sleep(time);
// }

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

// void ft_eat(t_philosoph *new_one)
// {
// 	// int time = rand() % new_one->args->t_eat;
// 	// unsigned long time = check_time() - new_one->args->start;
// 	// printf("%lu Philosopher #%d is eating...\n", check_time() - new_one->args->start, new_one->id + 1);
// 	// sleep(time);
//     // printf("%lu Philosopher #%d stopped eating...\n", check_time() - new_one->args->start, new_one->id + 1);
// }

// void test(pthread_mutex_t *fork)
// {

// 	if (state[p_id] == HUNGRY && state[new_one->l_fork] != EATING && state[new_one->right] != EATING)
// 	{
//        state[p_id] = EATING; //меняем статус, что наш i-й философ поел
//         pthread_mutex_unlock(&new_one->eaters[p_id]); //филосов начал есть, поэтому инкрементируем семафор, чтобы философа не заблокировали соседи
//     }
// }

// void ft_take_fork(t_philosoph *new_one)
// {
// 	//mutex
// 	// state = (unsigned int *)malloc(sizeof(unsigned int));
// 	// pthread_mutex_lock(&new_one->r_fork);
// 	// pthread_mutex_lock(&new_one->l_fork);
// 	pthread_mutex_lock(new_one->eaters);
// 	state[new_one->id] = HUNGRY;
// 	test(new_one, new_one->id); // попытка взять две вилки
// 	pthread_mutex_unlock(&new_one->r_fork);
// 	pthread_mutex_unlock(&new_one->l_fork);
// 	pthread_mutex_lock(&new_one->eaters[new_one->id]);
// }

void ft_put_fork(t_philosoph *new_one)
{
	pthread_mutex_lock(&new_one->r_fork);
	pthread_mutex_lock(&new_one->l_fork);
	// state[new_one->id] = THINKING;
	// test(&new_one->r_fork);
	// test(&new_one->r_fork);
	pthread_mutex_unlock(&new_one->r_fork);
	pthread_mutex_unlock(&new_one->l_fork);
}

//work for each phil
void *tread(void *new_one)
{
	while (1)
	{
		// ft_think(new_one);
		// ft_eating(new_one, tmp);
		// ft_take_fork(new_one);
		// t_philosoph *tmp = new_one;
		// ft_eat(new_one);
		// printf("Philosopher #%d is sleeping...\n", tmp->id + 1);
		// printf("Philosopher #%d is thinking...\n", tmp->id + 1);
		// ft_put_fork(new_one);
		// new_one->start_eat = tmp->start - check_time();
		print_status(new_one, "is sleeping");
		print_status(new_one, "is thinking");
	}

	// printf("%d\n", phil->die);
	// printf("allright");
	// exit(0);
}

t_philosoph *init_philo(t_all *args)
{
	t_philosoph *phil = NULL;
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	phil = (t_philosoph *)calloc(args->n_phil, sizeof(t_philosoph));
	while (j < args->n_phil)
	{
		phil->eaters = (pthread_mutex_t*)calloc(args->n_phil, sizeof(pthread_mutex_t));
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

void ft_check_philos(t_all *args)
{
	unsigned int num;
	int result;
	t_philosoph *new_one;
	// pthread_mutex_t *phil = NULL;


	num = 0;
	result = 0;
	// phil = malloc(sizeof(pthread_mutex_t));
	// pthread_mutex_init(phil, NULL);
	pthread_t *phil_treads = malloc(sizeof(pthread_t) * args->n_phil);
	new_one = init_philo(args);
	if(!phil_treads)
		printf("Malloc error\n");
	while (num < args->n_phil)
	{
		if(num % 2 == 0)
		{
			args->start = check_time(); //start simulation
			// printf("секунды:% ld\nnmicro секунд:% d\n", current_time.tv_sec, current_time.tv_usec);
			result = pthread_create(&phil_treads[num], NULL, tread, &new_one[num]);
			// printf("%d\n", result);
			// if (result == 0)
			// 	printf("pthread_create\n");
			// else
			// {
			// 	printf("pthread_not_create\n");
			// 	exit(EXIT_FAILURE);
			// }
		}
		// printf("num_tread: %d\n", num);
		// printf("thread_n %d\n", args->tread_n);
		// usleep(50);
		num++;
	}
	num = 0;
	while (num < args->n_phil)
	{
		if (num % 2 != 0)
		{
			args->start = check_time(); //start simulation
			// printf("секунды:% ld\nnmicro секунд:% d\n", current_time.tv_sec, current_time.tv_usec);
			result = pthread_create(&phil_treads[num], NULL, tread, &new_one[num]);
			// printf("%d\n", result);
			// if (result == 0)
			// 	printf("pthread_create\n");
			// else
			// {
			// 	printf("pthread_not_create\n");
			// 	exit(EXIT_FAILURE);
			// }
		}
		// usleep(50);
		num++;
	}
	usleep(1000);
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
	if(digit == 0)
	{
		if(argc == 5 || argc == 6)
		{
			if(argc == 6)
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
	//pthread_create(&id, NULL, tread, NULL);
	return (0);
}
