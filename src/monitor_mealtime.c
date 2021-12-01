/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_mealtime.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:34:14 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/01 18:16:30 by mjacq            ###   ########.fr       */
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
	if (update == dead)
			philo->philos_state->dead_philosophers++;
}

void	*monitor_mealtime(void *phil)
{
	t_philo	*philo;
	uint	last_mealtime;
	uint	curr_time;

	philo = phil;
	while (!status_should_stop(philo->philos_state))
	{
		usleep(100);
		last_mealtime = monitor_get_lastmealtime(philo);
		curr_time = f_timestamp_get(&philo->param->tv_start);
		if (curr_time - last_mealtime > (uint)philo->param->tt_die)
		{
			monitor_update_status(philo, dead);
			print_action(curr_time, philo->id, died, &philo->mu_output->stdout);
		}
	}
	return (NULL);
}
