/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_mealtime.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:34:14 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/01 17:46:39 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint	monitor_get_lastmealtime(t_philo *philo)
{
	uint	last_mealtime;

	last_mealtime = philo->activity.last_mealtime;
	return (last_mealtime);
}

void	monitor_update_status(t_philo *philo, t_status_update update)
{
	t_error	err;

	err = 0;
	if (update == dead)
	{
		err = pthread_mutex_lock(&philo->philos_state->mu);
		if (!err)
		{
			philo->philos_state->dead_philosophers++;
			pthread_mutex_unlock(&philo->philos_state->mu);
		}
	}
}

void	*monitor_mealtime(void *phil)
{
	t_philo	*philo;
	uint	last_mealtime;
	uint	current_time;

	philo = phil;
	while (!status_should_stop(philo->philos_state))
	{
		usleep(100);
		last_mealtime = monitor_get_lastmealtime(philo);
		current_time = f_timestamp_get(&philo->param->tv_start);
		if (current_time - last_mealtime > (uint)philo->param->tt_die)
			monitor_update_status(philo, dead);
	}
	return (NULL);
}
