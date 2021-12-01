/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:09:51 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/01 18:41:07 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_until_starvation(t_philo *philo)
{
	while (!philo_should_stop(philo))
		usleep(10);
}

static void	philo_cycle(t_philo *philo)
{
	philo_take_forks(philo);
	if (philo->forks.right_taken)
	{
		philo_do(philo, eating);
		philo_do(philo, sleeping);
		philo_do(philo, thinking);
	}
	else
		wait_until_starvation(philo);
}

void	*philo_job(void *phil)
{
	t_philo		*philo;
	pthread_t	monitor_tid;

	philo = phil;
	pthread_create(&monitor_tid, NULL, monitor_mealtime, philo);
	while (!philo_should_stop(philo))
		philo_cycle(philo);
	philo_replace_forks(philo);
	if (philo->error)
		philo_update_status(philo, error_occured);
	pthread_join(monitor_tid, NULL);
	return (NULL);
}
