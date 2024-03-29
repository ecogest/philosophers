/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:12:01 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/02 18:31:36 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
** ================================ Includes ================================ **
*/

# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_MS_SLEEP_TIME 100
# define COLOR 0

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

typedef enum e_status_update
{
	sated,
	dead,
	error_occured
}	t_status_update;

/*
** =============================== Structures =============================== **
*/

typedef struct s_action_fmt
{
	t_action	action;
	const char	*color;
	const char	*stract;
}				t_fmt;

typedef struct s_philo_param
{
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				max_meal;
}					t_philo_param;

typedef struct s_forks
{
	bool			left_taken;
	bool			right_taken;
	pthread_mutex_t	left;
	pthread_mutex_t	*right;
}					t_forks;

typedef struct s_activity
{
	t_action				type;
	uint					start;
	_Atomic volatile uint	last_mealtime;
}							t_activity;

typedef struct s_mutex_output
{
	pthread_mutex_t	stdout;
	pthread_mutex_t	stderr;
}					t_mutex_output;

typedef struct s_philos_state
{
	_Atomic volatile int		hungry_philosphers;
	_Atomic volatile int		dead_philosophers;
	_Atomic volatile t_error	error;
	pthread_mutex_t				mu_check_death;
}								t_philos_state;

typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	t_philo_param	*param;
	t_philos_state	*philos_state;
	t_activity		activity;
	int				meal_count;
	t_forks			forks;
	t_mutex_output	*mu_output;
	t_error			error;
}					t_philo;

typedef struct s_philos
{
	int				count;
	t_philos_state	philos_state;
	t_philo			*array;
	t_error			error;
}			t_philos;

typedef struct s_root
{
	t_philo_param	philo_param;
	t_mutex_output	mu_output;
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
void	philo_do(t_philo *philo, t_action action);
void	philo_timestamp_start(t_philo *philo);
void	philo_take_forks(t_philo *philo);
void	philo_pick_a_fork(t_philo *philo);
void	philo_replace_forks(t_philo *philo);
bool	philo_should_stop(t_philo *philo);
void	philo_ms_sleep(t_philo *philo, uint ms_start, uint ms_duration);

// Printing actions
void	put_action(uint timestamp, int id, t_action action);
int		mu_put_action(uint timestamp, int id, t_action action, \
		pthread_mutex_t *mu_stdout);
void	philo_put_action(t_philo *philo);

// status checking
bool	status_should_stop(t_philos_state *status);
bool	philo_should_stop(t_philo *philo);
void	status_update(t_philos_state *status, t_status_update update);
void	philo_update_status(t_philo *philo, t_status_update update);

// monitor
void	*monitor_mealtime(void	*phil);

// action params
int		action_get_ms_duration(t_action action, t_philo_param *param);

// Syscall wrapped
void	*f_calloc(size_t block_size, size_t count, t_error *error);
void	f_mutex_init(pthread_mutex_t *mu, t_error *error);
void	f_mu_lock(pthread_mutex_t *mu, t_error *error);
void	f_mu_unlock(pthread_mutex_t *mu, t_error *error);
void	f_thread(t_philo *philo, void *(*job)(void *), t_error *error);

// Misc utils
uint	f_timestamp_get(void);

// Printing messages
void	f_puterr(const char *s);
void	f_puterr_safe(const char *s, pthread_mutex_t *mu_stderr);
void	f_put_usage(void);

// Cleanup functions
void	root_cleanup(t_root *all);
void	philos_cleanup(t_philos *philos);

// ft
int		ft_isnumber(const char *str);
int		ft_isint(const char *str);
int		ft_atoi(const char *str);
void	ft_putstr_fd(const char *s, int fd);
size_t	ft_strlen(const char *str);

#endif
