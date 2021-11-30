/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:09:51 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/30 13:11:48 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_get_time(t_philo *philo)
{
	struct timeval	tv;

	if (philo->error)
		return ;
	philo->error = gettimeofday(&tv, NULL);
	philo->state.timestamp = f_tv_to_timestamp(&tv, &philo->param->tv_start);
}

void	philo_do(t_philo *philo, t_action action)
{
	int	duration;

	if (philo->error)
		return ;
	philo->state.action = action;
	if (action == taking_lfork || action == taking_rfork)
		philo_take_fork(philo);
	philo_get_time(philo);
	philo_print_action(philo);
	duration = action_get_duration(action, philo->param);
	if (duration)
		f_ms_sleep(duration);
	if (action == eating)
		philo_replace_forks(philo);
}

void	philo_cycle(t_philo *philo)
{
	philo_do(philo, taking_lfork);
	philo_do(philo, taking_rfork);
	philo_do(philo, eating);
	philo->meal_count++;
	philo_do(philo, sleeping);
	philo_do(philo, thinking);
}

void	*philo_job(void *phil)
{
	t_philo	*philo;

	philo = phil;
	while (philo->meal_count != philo->param->max_meal)
	{
		philo_cycle(philo);
		if (philo->error)
			break ;
	}
	return (NULL);
}
