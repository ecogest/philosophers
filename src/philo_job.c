/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:09:51 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/29 18:57:24 by mjacq            ###   ########.fr       */
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

void	philo_cycle(t_philo *philo)
{
	philo_get_time(philo);
	pthread_mutex_lock(philo->mu_stdout);
	printf("tid: %ld - timestamp: %u\n", philo->tid, philo->state.timestamp);
	pthread_mutex_unlock(philo->mu_stdout);
	sleep(1);
	philo->meal_count++;
}

void	*philo_job(void *phil)
{
	t_philo	*philo;

	philo = phil;
	while (philo->meal_count != philo->param->max_meal)
	{
		philo_cycle(philo);
	}
	return (NULL);
}
