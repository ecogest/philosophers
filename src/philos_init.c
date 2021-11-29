/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:25:47 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/29 13:25:54 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_fill_params(t_philo *philo, t_all *all)
{
	*philo = (t_philo){\
		.param = &all->philo_param, \
		.mu_stdout = &all->mu_stdout \
	};
}

/*
** @brief Alloc the array of philos, and pass each of them their params
*/

void	philos_init(t_philos *philos, t_all *all)
{
	int		i;
	t_philo	*philo;

	philos->array = f_calloc(philos->count, sizeof(*philos->array), \
			&philos->error);
	if (!philos->error)
	{
		i = 0;
		while (i < philos->count)
		{
			philo = &philos->array[i];
			philo_fill_params(philo, all);
			i++;
		}
	}
}
