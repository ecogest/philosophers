/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ms_sleep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:16:03 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/02 15:16:55 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ms_sleep_refresh(t_philo *philo, uint ms_start, uint ms_duration, \
		uint mus_refresh_interval)
{
	while (!philo_should_stop(philo) && \
			1000 * f_timestamp_get() + mus_refresh_interval + 100 \
			< 1000 * (ms_start + ms_duration))
		usleep(mus_refresh_interval);
}

void	philo_ms_sleep(t_philo *philo, uint ms_start, uint ms_duration)
{
	ms_sleep_refresh(philo, ms_start, ms_duration, 2000);
	ms_sleep_refresh(philo, ms_start, ms_duration, 1000);
	ms_sleep_refresh(philo, ms_start, ms_duration, 300);
}
