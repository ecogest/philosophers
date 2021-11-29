/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:24:29 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/29 13:50:15 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO:
void	philos_lock_start(t_philos *philos)
{
	(void)philos;
}

// TODO:
void	philos_create_threads(t_philos *philos)
{
	(void)philos;
}

// TODO:
void	philos_run_threads(t_philos *philos)
{
	(void)philos;
}

void	all_init(t_all *all)
{
	*all = (t_all){.philo_param.max_meal = -1};
	pthread_mutex_init(&all->mu_stdout, NULL);
}

int	main_philo(int ac, const char **av)
{
	t_all	all;

	all_init(&all);
	f_parse_av(&all, ac, av);
	if (!all.error)
	{
		philos_init(&all.philos, &all);
		philos_lock_start(&all.philos);
		philos_create_threads(&all.philos);
		philos_run_threads(&all.philos);
		if (all.philos.error)
			all.error = all.philos.error;
	}
	all_cleanup(&all);
	return (all.error);
}
