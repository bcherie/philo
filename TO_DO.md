
t_all

{
	int				n_phil;
	unsigned long 	t_die;
	unsigned long	t_eat;
	unsigned long	t_sleep;
	unsigned long	eat_times;
	unsigned long	start;
	pthread_mutex_t	*print;
	pthread_mutex_t *forks;
	t_philo			*phil;
	pthread			*thread;
	int				flag_die;

	// int				state; // state phil
	// t_philosoph		*new_one;
}				t_all;


typedef struct s_philosoph
{
	int				id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;

	int				countEat;
	unsigned long	start_eat;
	unsigned long	last_eat;
}				t_philosoph;
