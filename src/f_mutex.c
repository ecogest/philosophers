/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_mutex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:55:57 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/30 13:55:46 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

	/* if (*error) */
	/* 	f_puterr("Mutex initialisation failed."); */
void	f_mutex_init(pthread_mutex_t *mu, t_error *error)
{
	if (*error)
		return ;
	*error = pthread_mutex_init(mu, NULL);
}

	/* if (*error) */
	/* 	f_puterr("Mutex lock failed."); */
void	f_mu_lock(pthread_mutex_t *mu, t_error *error)
{
	if (*error)
		return ;
	*error = pthread_mutex_lock(mu);
}

	/* if (*error) */
	/* 	f_puterr("Mutex unlock failed."); */
void	f_mu_unlock(pthread_mutex_t *mu, t_error *error)
{
	if (*error)
		return ;
	*error = pthread_mutex_unlock(mu);
}
