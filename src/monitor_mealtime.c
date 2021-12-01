/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_mealtime.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:34:14 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/01 19:17:44 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint	monitor_get_lastmealtime(t_philo *philo)
{
	uint	last_mealtime;

	last_mealtime = philo->activity.last_mealtime;
	return (last_mealtime);
}

void	monitor_trigger_death(t_philo *philo, uint curr_time)
{
	pthread_mutex_lock(&philo->philos_state->mu_check_death);
	philo->philos_state->dead_philosophers++;
	if (philo->philos_state->dead_philosophers == 1)
		print_action(curr_time, philo->id, died, &philo->mu_output->stdout);
	pthread_mutex_unlock(&philo->philos_state->mu_check_death);
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
			monitor_trigger_death(philo, curr_time);
	}
	return (NULL);
}
