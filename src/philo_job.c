/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:09:51 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/30 10:41:38 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_get_time(t_philo *philo)
{
	struct timeval	tv;
	struct timeval	diff;

	gettimeofday(&tv, NULL);
	diff.tv_sec = tv.tv_sec - philo->param->tv_start.tv_sec;
	diff.tv_usec = tv.tv_usec - philo->param->tv_start.tv_usec;
	philo->state.timestamp = diff.tv_sec * 1000 + diff.tv_usec / 1000;
}

void	philo_do(t_philo *philo, t_action action)
{
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
