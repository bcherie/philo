#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philosoph
{
	int				id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_all	*phil_ar;
	int				countEat;
	unsigned long	last_eat;
}t_philosoph;

typedef struct s_all
{
	int				n_phil;
	unsigned long	t_die;
	unsigned long	t_eat;
	unsigned long	t_sleep;
	int				eat_times;
	unsigned long	start;
	pthread_mutex_t	*print;
	pthread_mutex_t	*forks;
	pthread_t		*phil_tread;
	t_philosoph		*phil;
	int				flag_die;
	int				digit;
}t_all;

void			ft_init(t_all *args);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
void			ft_pthread_create(t_all *args);
long unsigned	check_time(void);
void			stop_tread(t_all *args);
void			check_death(t_all *args);
void			ft_take_fork(t_philosoph *phil);
void			ft_print_status(t_philosoph *phil, char *status);
void			ft_check_args(t_all *args, char **argv);
void			ft_fill_args(t_all *args, int argc, char **argv);
void			ft_init_mutex(t_all *args);
void			ft_wait(useconds_t t);
void			ft_errors(void);

#endif
