/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:42:37 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/30 15:57:40 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_cleanup(t_philo *philo)
{
	pthread_mutex_destroy(&philo->forks.left);
}

void	philos_cleanup(t_philos *philos)
{
	int		i;
	t_philo	*philo;

	if (philos->array)
	{
		pthread_mutex_destroy(&philos->status.mu);
		i = 0;
		while (i < philos->count)
		{
			philo = &philos->array[i];
			philo_cleanup(philo);
			i++;
		}
		free(philos->array);
		philos->array = NULL;
	}
}

void	root_cleanup(t_root *all)
{
	philos_cleanup(&all->philos);
	pthread_mutex_destroy(&all->mu.stdout);
	pthread_mutex_destroy(&all->mu.stderr);
	pthread_mutex_destroy(&all->mu.start);
}
