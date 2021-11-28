/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:12:01 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/28 16:35:02 by mjacq            ###   ########.fr       */
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

/*
** =============================== Structures =============================== **
*/

typedef struct s_philo_param
{
	size_t	tt_die;
	size_t	tt_eat;
	size_t	tt_sleep;
	size_t	max_meal;
}			t_philo_param;

typedef struct s_forks
{
	pthread_mutex_t	left;
	pthread_mutex_t	*right;
}					t_forks;

typedef struct s_philo
{
	pthread_t		tid;
	t_philo_param	*param;
	t_forks			forks;
	pthread_mutex_t	*mu_stdout;
}					t_philo;

typedef struct s_philos
{
	size_t	philo_count;
	t_philo	*array;
}			t_philos;

typedef struct s_all
{
	t_philo_param	philo_param;
	pthread_mutex_t	mu_stdout;
	t_philos		philos;
	t_error			error;
}					t_all;

/*
** =============================== Functions ================================ **
*/

void	f_parse_av(t_all *all, int ac, const char **av);

#endif
