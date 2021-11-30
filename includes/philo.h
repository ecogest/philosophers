/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:12:01 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/30 16:42:34 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
** ================================ Includes ================================ **
*/

# include "libft.h" // TODO: Remove libft
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

/*
** ================================= Enums ================================== **
*/

typedef enum e_error
{
	success = 0,
	error,
	error_av,
	error_malloc
}	t_error;

typedef enum e_action
{
	unset = 0,
	eating,
	sleeping,
	thinking,
	taking_lfork,
	taking_rfork,
	died
}	t_action;

/*
** =============================== Structures =============================== **
*/

typedef struct s_action_display
{
	t_action	action;
	const char	*color;
	const char	*stract;
}				t_act_d;

typedef struct s_philo_param
{
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				max_meal;
	struct timeval	tv_start;
}					t_philo_param;

typedef struct s_forks
{
	pthread_mutex_t	left;
	pthread_mutex_t	*right;
}					t_forks;

typedef struct s_activity
{
	uint		start;
	uint		delta_time;
	t_action	type;
}				t_activity;

typedef struct s_mutex_root
{
	pthread_mutex_t	stdout;
	pthread_mutex_t	stderr;
	pthread_mutex_t	start;
}					t_mutex_root;

typedef enum e_status_update
{
	sated,
	dead,
	error_occured
}	t_status_update;

typedef struct s_philos_status
{
	int				hungry_philosphers;
	int				dead_philosophers;
	t_error			error;
	pthread_mutex_t	mu;
}					t_philos_status;

typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	t_philo_param	*param;
	t_philos_status	*status;
	t_activity		activity;
	int				meal_count;
	t_forks			forks;
	t_mutex_root	*mu;
	t_error			error;
}					t_philo;

typedef struct s_philos
{
	int				count;
	t_philo			*array;
	t_philos_status	status;
	t_error			error;
}			t_philos;

typedef struct s_root
{
	t_philo_param	philo_param;
	t_mutex_root	mu;
	t_philos		philos;
	t_error			error;
}					t_root;

/*
** =============================== Functions ================================ **
*/

// Main frame
int		main_philo(int ac, const char **av);
void	root_init(t_root *root);
void	root_parse_av(t_root *all, int ac, const char **av);
void	philos_init(t_philos *philos, t_root *all);

// job functions
void	*philo_job(void *phil);
void	philo_get_time(t_philo *philo);
void	philo_print_action(t_philo *philo);
void	philo_take_fork(t_philo *philo);
void	philo_replace_forks(t_philo *philo);
bool	philo_should_stop(t_philo *philo);

// status checking
bool	philo_should_stop(t_philo *philo);
void	philo_update_status(t_philo *philo, t_status_update update);

// action params
int		action_get_duration(t_action action, t_philo_param *param);
t_act_d	action_get_display(t_action action);

// Syscall wrapped
void	*f_calloc(size_t block_size, size_t count, t_error *error);
void	f_mutex_init(pthread_mutex_t *mu, t_error *error);
void	f_mu_lock(pthread_mutex_t *mu, t_error *error);
void	f_mu_unlock(pthread_mutex_t *mu, t_error *error);
void	f_thread(t_philo *philo, void *(*job)(void *), t_error *error);
void	f_ms_sleep(int millisec);

// Misc utils
uint	f_tv_to_timestamp(struct timeval *now, struct timeval *start);

// Printing messages
void	f_puterr(const char *s);
void	f_put_usage(void);

// Cleanup functions
void	root_cleanup(t_root *all);
void	philos_cleanup(t_philos *philos);

#endif
