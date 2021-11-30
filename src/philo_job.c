/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:09:51 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/30 17:21:51 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_activity_start(t_philo *philo)
{
	struct timeval	tv;

	if (philo->error)
		return ;
	philo->error = gettimeofday(&tv, NULL);
	philo->activity.start = f_tv_to_timestamp(&tv, &philo->param->tv_start);
	if (philo->activity.type == eating)
		philo->activity.last_meal = philo->activity.start;
}

void	philo_do(t_philo *philo, t_action action)
{
	int	duration;

	if (philo_should_stop(philo))
		return ;
	philo->activity.type = action;
	if (action == taking_lfork || action == taking_rfork)
		philo_pick_a_fork(philo);
	philo_activity_start(philo);
	philo_print_action(philo);
	duration = action_get_duration(action, philo->param);
	if (duration)
		f_ms_sleep(duration);
	if (action == eating)
		philo_replace_forks(philo);
}

/*
** We want the neighbours to compete for the same fork first
** Then the winner can take the second one
** Otherwise every philosopher could end up with only one fork.
*/

void	philo_take_forks(t_philo *philo)
{
	if (philo->error)
		return ;
	if (philo->id % 2)
	{
		philo_do(philo, taking_lfork);
		philo_do(philo, taking_rfork);
	}
	else
	{
		philo_do(philo, taking_rfork);
		philo_do(philo, taking_lfork);
	}
}

void	philo_cycle(t_philo *philo)
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
	f_mu_lock(&philo->mu->start, &philo->error);
	f_mu_unlock(&philo->mu->start, &philo->error);
	while (!philo_should_stop(philo))
	{
		philo_cycle(philo);
		if (philo->error)
			break ;
	}
	return (NULL);
}
