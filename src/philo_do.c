/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:17:22 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/01 13:52:01 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_timestamp_start(t_philo *philo)
{
	if (philo->error)
		return ;
	philo->activity.start = f_timestamp_get(&philo->param->tv_start);
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

void	philo_wait_for_action_to_finish(t_philo *philo, t_action action)
{
	int	duration;

	duration = action_get_duration(action, philo->param);
	if (duration)
		f_ms_sleep(duration);
}

void	philo_do(t_philo *philo, t_action action)
{
	philo->activity.type = action;
	if (action == taking_lfork || action == taking_rfork)
		philo_pick_a_fork(philo);
	if (philo_should_stop(philo))
		return ;
	philo_timestamp_start(philo);
	philo_print_action(philo);
	philo_wait_for_action_to_finish(philo, action);
	if (action == eating)
		philo_finished_eating(philo);
}
