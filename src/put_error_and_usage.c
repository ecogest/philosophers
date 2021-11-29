/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error_and_usage.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:34:42 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/29 11:49:29 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	f_puterr(const char *s)
{
	ft_putstr_fd("\e[31mError: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\e[0m\n", 2);
}

void	f_usage(void)
{
	ft_putstr_fd("\e[33mUsage: \e[1m./philo\e[0;33m number_of_philosophers " \
			"time_to_die time_to_eat time_to_sleep " \
			"[number_of_times_each_philosopher_must_eat]\n", 2);
}
