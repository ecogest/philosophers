/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:17:22 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/02 15:16:10 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_timestamp_start(t_philo *philo)
{
	if (philo->error)
		return ;
	philo->activity.start = f_timestamp_get();
	if (philo->activity.type == eating)
		philo->activity.last_mealtime = philo->activity.start;
}

void	philo_finished_eating(t_philo *philo)
{
	philo_replace_forks(philo);
	philo->meal_count++;
	if (philo->meal_count == philo->param->max_meal)
		philo_update_status(philo, sated);
}

/*
** Idea: could set a duration for thinking as well
**	else if (action == thinking)
**	{
**		ms_start = philo->activity.last_mealtime;
**		if (philo->param->tt_die > 10)
**			ms_duration = philo->param->tt_die - 10;
**	}
*/

void	philo_wait_for_action_to_finish(t_philo *philo, t_action action)
{
	int	ms_duration;
	int	ms_start;

	ms_duration = 0;
	if (action == eating || action == sleeping)
	{
		ms_start = philo->activity.start;
		ms_duration = action_get_ms_duration(action, philo->param);
	}
	if (ms_duration)
		philo_ms_sleep(philo, ms_start, ms_duration);
}

void	philo_do(t_philo *philo, t_action action)
{
	philo->activity.type = action;
	if (action == taking_lfork || action == taking_rfork)
		philo_pick_a_fork(philo);
	philo_put_action(philo);
	philo_wait_for_action_to_finish(philo, action);
	if (action == eating)
		philo_finished_eating(philo);
}
