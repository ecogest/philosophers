/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:09:51 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/01 10:39:15 by mjacq            ###   ########.fr       */
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

void	philo_do(t_philo *philo, t_action action)
{
	int	duration;

	if (philo_should_stop(philo))
		return ;
	philo->activity.type = action;
	if (action == taking_lfork || action == taking_rfork)
		philo_pick_a_fork(philo);
	philo_timestamp_start(philo);
	philo_print_action(philo);
	duration = action_get_duration(action, philo->param);
	if (duration)
		f_ms_sleep(duration);
	if (action == eating)
		philo_replace_forks(philo);
}

static void	philo_cycle(t_philo *philo)
{
	philo_take_forks(philo);
	philo_do(philo, eating);
	philo->meal_count++;
	if (philo->meal_count == philo->param->max_meal)
		philo_update_status(philo, sated);
	philo_do(philo, sleeping);
	philo_do(philo, thinking);
}

void	*philo_job(void *phil)
{
	t_philo	*philo;

	philo = phil;
	while (!philo_should_stop(philo))
	{
		philo_cycle(philo);
		if (philo->error)
			break ;
	}
	return (NULL);
}
