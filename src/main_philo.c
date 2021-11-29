/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:24:29 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/29 13:27:32 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_lock_start(t_philos *philos)
{
	(void)philos;
}

void	philos_create_threads(t_philos *philos)
{
	(void)philos;
}

void	philos_run_threads(t_philos *philos)
{
	(void)philos;
}

int	main_philo(int ac, const char **av)
{
	t_all	all;

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
	return (all.error);
}
