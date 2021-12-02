/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:24:29 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/02 19:03:38 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_create_threads(t_philos *philos)
{
	static int	half_created;
	static int	i;
	t_philo		*philo;

	if (philos->error)
		return ;
	while (i < philos->count)
	{
		philo = &philos->array[i];
		f_thread(philo, philo_job, &philos->error);
		if (philos->error)
			break ;
		i += 2;
	}
	if (!half_created)
	{
		half_created = 1;
		i = 1;
		usleep(100);
		philos_create_threads(philos);
	}
}

void	philos_wait(t_philos *philos)
{
	int		i;
	t_philo	*philo;

	if (!philos)
		return ;
	i = 0;
	while (i < philos->count)
	{
		philo = &philos->array[i];
		if (philo->tid)
		{
			pthread_join(philo->tid, NULL);
			if (philo->error)
				philos->error = philo->error;
		}
		i++;
	}
}

int	main_philo(int ac, const char **av)
{
	t_root	root;

	root_init(&root);
	root_parse_av(&root, ac, av);
	if (!root.error)
	{
		philos_init(&root.philos, &root);
		f_timestamp_get();
		philos_create_threads(&root.philos);
		philos_wait(&root.philos);
	}
	if (root.error || root.philos.error || root.philos.philos_state.error)
		root.error = EXIT_FAILURE;
	root_cleanup(&root);
	return (root.error);
}
