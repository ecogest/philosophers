/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:24:29 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/29 18:24:38 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO:
void	philos_lock_start(t_philos *philos)
{
	if (philos->error)
		return ;
}

// TODO: check return of pthread_create
void	philos_create_threads(t_philos *philos)
{
	t_philo	*philo;
	int		i;

	if (philos->error)
		return ;
	i = 0;
	while (i < philos->count)
	{
		philo = &philos->array[i];
		pthread_create(&philo->tid, NULL, philo_job, (void *)philo);
		i++;
	}
}

// TODO:
void	philos_run_threads(t_philos *philos)
{
	if (philos->error)
		return ;
}

int	main_philo(int ac, const char **av)
{
	t_root	root;

	root_init(&root);
	root_parse_av(&root, ac, av);
	if (!root.error)
	{
		philos_init(&root.philos, &root);
		philos_lock_start(&root.philos);
		gettimeofday(&root.philo_param.tv_start, NULL);
		philos_create_threads(&root.philos);
		philos_run_threads(&root.philos);
		if (root.philos.error)
			root.error = root.philos.error;
	}
	root_cleanup(&root);
	return (root.error);
}
