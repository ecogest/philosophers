/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_mutex_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:55:57 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/29 13:59:26 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	f_mutex_init(pthread_mutex_t *mu, t_error *error)
{
	if (!*error)
		*error = pthread_mutex_init(mu, NULL);
	if (*error)
		f_puterr("Mutex initialisation failed.");
}
