#ifndef PHILOSOFERS_H
# define PHILOSOFERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

//https://acm.bsu.by/wiki/Unix2019b/%D0%91%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA%D0%B0_pthreads
// typedef struct s_all
// {
// 	//get number philosoph
// 	int				n_phil;
// 	unsigned long 	t_die;
// 	unsigned long	t_eat;
// 	unsigned long	t_sleep;
// 	unsigned long	eat_times;
// 	unsigned long	start;
// 	unsigned long	last_eat;
// 	pthread_mutex_t	*print;
// 	int				flag_die;

// 	// int				state; // state phil
// 	// t_philosoph		*new_one;
// }				t_all;

// typedef struct s_philosoph
// {
// 	int	id;
// 	pthread_mutex_t	*l_fork;
// 	pthread_mutex_t	*r_fork;
// 	pthread_mutex_t *eaters;
// 	pthread_mutex_t *death;
// 	// pthread_mutex_t	*print;
// 	int				*status_die;
// 	// int				flag_die;
// 	// unsigned long	start_eat;
// 	int				countEat;
// 	// unsigned long	last_eat;
// 	t_all			*args;
// }				t_philosoph;

typedef struct s_philosoph
{
	int				id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_all	*phil_ar;
	int				countEat;
	unsigned long	start_eat;
	unsigned long	last_eat;
}				t_philosoph;

typedef struct s_all

{
	int				n_phil;
	unsigned long 	t_die;
	unsigned long	t_eat;
	unsigned long	t_sleep;
	int				eat_times;
	unsigned long	start;
	pthread_mutex_t	*print;
	pthread_mutex_t *forks;
	t_philosoph		*phil;
	int				flag_die;
	int				digit;

	// int				state; // state phil
	// t_philosoph		*new_one;
}				t_all;

// typedef struct s_philosoph
// {
// 	int				id;
// 	pthread_mutex_t	*l_fork;
// 	pthread_mutex_t	*r_fork;
// 	// t_all			*args;
// 	int				countEat;
// 	unsigned long	start_eat;
// 	unsigned long	last_eat;
// }				t_philosoph;

void ft_init(t_all *args);
t_philosoph *init_philo(t_all *args);
int	ft_atoi(const char *str);
int	ft_isdigit(int c);
// void ft_check_philos(t_all *args);
// void ft_check_philos(t_all *args, t_philosoph **new_one);
void ft_pthread_create(t_all *args);
long unsigned	check_time(void);
void my_usleep(t_philosoph *phil);
void ft_sleep(t_philosoph *new_one);
void	*ft_memset(void *dest, int c, size_t n);
// void stop_tread(t_philosoph *new_one, pthread_t *phil_treads);
void stop_tread(t_all *args, pthread_t *phil_treads);
void check_death(t_all *args);
// void ft_take_fork(t_all *phil);
void ft_take_fork(t_philosoph *phil);
// void	ft_print_status(t_all *args, char *status);
void	ft_print_status(t_philosoph *phil, char *status);
void ft_check_args(t_all *args, char **argv);
void ft_fill_args(t_all *args, int argc, char **argv);
void ft_init_mutex(t_all *args);
void my_useat(t_philosoph *phil);
void	ft_usleep(useconds_t time);
int ft_check_eat(t_all *args);



#endif
