/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error_and_usage.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:34:42 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/01 10:23:13 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	f_puterr(const char *s)
{
	ft_putstr_fd("\e[31mError: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\e[0m\n", 2);
}

void	f_puterr_safe(const char *s, pthread_mutex_t *mu_stderr)
{
	pthread_mutex_lock(mu_stderr);
	f_puterr(s);
	pthread_mutex_unlock(mu_stderr);
}

void	f_put_usage(void)
{
	ft_putstr_fd("\e[33mUsage: \e[1m./philo\e[0;33m number_of_philosophers " \
			"time_to_die time_to_eat time_to_sleep " \
			"[number_of_times_each_philosopher_must_eat]\e[0m\n", 2);
}
