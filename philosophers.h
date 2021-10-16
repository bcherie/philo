#ifndef PHILOSOFERS_H
# define PHILOSOFERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

//https://acm.bsu.by/wiki/Unix2019b/%D0%91%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA%D0%B0_pthreads
typedef struct s_all
{
	//get number philosoph
	int				n_phil;
	unsigned long	t_die;
	unsigned long	t_eat;
	unsigned long	t_sleep;
	unsigned long	eat_times;
	unsigned long	start;
	pthread_mutex_t	*print;
	int				flag_die;

	// int				state; // state phil
	// t_philosoph		*new_one;
}				t_all;

typedef struct s_philosoph
{
	int	id;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
	pthread_mutex_t *eaters;
	pthread_mutex_t *death;
	pthread_mutex_t	*print;
	int				*status_die;
	// int				flag_die;
	unsigned long	start_eat;
	int				countEat;
	unsigned long	last_eat;
	t_all			*args;
}				t_philosoph;


void ft_init(t_all *args);
t_philosoph *init_philo(t_all *args);
int	ft_atoi(const char *str);
int	ft_isdigit(int c);
void ft_check_philos(t_all *args);
long unsigned	check_time(void);
void my_usleep(unsigned long t_eat);
void ft_sleep(t_philosoph *new_one);
void	*ft_memset(void *dest, int c, size_t n);
void stop_tread(t_philosoph *new_one, pthread_t *phil_treads);
int	ft_strlen(const char *str);

#endif
