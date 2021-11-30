/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:09:51 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/30 11:07:30 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint	tv_to_timestamp(struct timeval *now, struct timeval *start)
{
	struct timeval	diff;

	diff.tv_sec = now->tv_sec - start->tv_sec;
	diff.tv_usec = now->tv_usec - start->tv_usec;
	return (diff.tv_sec * 1000 + diff.tv_usec / 1000);
}

void	philo_get_time(t_philo *philo)
{
	struct timeval	tv;

	if (philo->error)
		return ;
	philo->error = gettimeofday(&tv, NULL);
	philo->state.timestamp = tv_to_timestamp(&tv, &philo->param->tv_start);
}

void	philo_do(t_philo *philo, t_action action)
{
	if (philo->error)
		return ;
	philo->state.action = action;
	philo_get_time(philo);
	philo_print_action(philo);
	usleep(philo->param->tt_sleep * 1000);
}

void	philo_cycle(t_philo *philo)
{
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
