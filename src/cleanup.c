/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:42:37 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/30 13:45:49 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_cleanup(t_philo *philo)
{
	if (philo->tid)
		pthread_join(philo->tid, NULL);
	pthread_mutex_destroy(&philo->forks.left);
}

void	philos_cleanup(t_philos *philos)
{
	int		i;
	t_philo	*philo;

	if (philos->array)
	{
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
	pthread_mutex_destroy(&all->mu_stdout);
}
