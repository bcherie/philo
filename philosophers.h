#ifndef PHILOSOFERS_H
# define PHILOSOFERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
// #define LEFT (i + N - 1) % N //макрос, определяющий номер левого философа
// #define RIGHT (i + 1) % N //макрос, определяющий номер правого философа
#define THINKING 0 //код состояния, когда философ размышляет
#define HUNGRY 1 //код состояния, когда философ хочет поесть (ожидает палочки)
#define EATING 2 //код состояния, когда философ ест
// int* state = NULL;
// typedef struct s_timeval
// {
// 	long    tv_sec;         /* секунды */
// 	long    tv_usec;        /* микросекунды */
// }				t_timeval;
//args struct

//https://acm.bsu.by/wiki/Unix2019b/%D0%91%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA%D0%B0_pthreads
typedef struct s_all
{
	//get number philosoph
	int	n_phil;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	eat_times;
	unsigned long	start;
	int				flag_die;

	// int				state; // state phil
	int				p_id;
	// t_philosoph		*new_one;
}				t_all;

typedef struct s_philosoph
{
	unsigned int	id;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
	pthread_mutex_t *eaters;
	pthread_mutex_t *death;
	// int				flag_die;
	unsigned long	start_eat;
	int				countEat;
	unsigned long	last_eat;
	// unsigned char	left_fork;
	// unsigned char	right_fork;
	int	left;
	int	right;
	t_all			*args;
}				t_philosoph;


// int gettimeofday(struct timeval *tv, struct timezone *tz);
void ft_init(t_all *args);
t_philosoph *init_philo(t_all *args);
int	ft_atoi(const char *str);
int	ft_isdigit(int c);
long unsigned	check_time(void);
void my_usleep(unsigned long t_eat);
void ft_sleep(t_philosoph *new_one);

#endif
