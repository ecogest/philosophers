/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:25:47 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/30 12:56:26 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_fill_params(t_philo *philo, t_root *all)
{
	*philo = (t_philo){\
		.param = &all->philo_param, \
		.mu_stdout = &all->mu_stdout \
	};
}

/*
** @brief return the neighbour from the right (NULL if none)
*/

static t_philo	*philo_get_neighbour(t_philos *philos, int i)
{
	t_philo	*neighbour;

	if (philos->count == 1)
		neighbour = NULL;
	else if (i < philos->count - 1)
		neighbour = &philos->array[i + 1];
	else
		neighbour = &philos->array[0];
	return (neighbour);
}

/*
** @brief Alloc the array of philos, pass their params and init forks
*/

void	philos_init(t_philos *philos, t_root *all)
{
	int		i;
	t_philo	*philo;
	t_philo	*neighbour;

	philos->array = f_calloc(philos->count, sizeof(*philos->array), \
			&philos->error);
	if (!philos->error)
	{
		i = 0;
		while (i < philos->count)
		{
			philo = &philos->array[i];
			philo_fill_params(philo, all);
			f_mutex_init(&philo->forks.left, &philo->error);
			neighbour = philo_get_neighbour(philos, i);
			if (neighbour)
				philo->forks.right = &neighbour->forks.left;
			i++;
		}
	}
}
