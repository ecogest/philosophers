/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:09:51 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/01 13:17:59 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_cycle(t_philo *philo)
{
	philo_take_forks(philo);
	philo_do(philo, eating);
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
	if (philo->forks.left_taken)
		pthread_mutex_unlock(&philo->forks.left);
	if (philo->forks.right_taken)
		pthread_mutex_unlock(philo->forks.right);
	return (NULL);
}
