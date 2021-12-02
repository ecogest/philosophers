/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ms_sleep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:16:03 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/02 16:04:33 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_ms_sleep(t_philo *philo, uint ms_start, uint ms_duration)
{
	uint	current_time;

	while (!philo_should_stop(philo))
	{
		current_time = f_timestamp_get();
		if (current_time >= (ms_start + ms_duration))
			break ;
		else
			usleep(1000 * ((ms_start + ms_duration) - current_time) / 2);
	}
}
