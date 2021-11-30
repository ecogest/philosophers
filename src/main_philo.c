/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:24:29 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/30 14:39:37 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_lock_start(t_philos *philos, pthread_mutex_t *mu_start)
{
	if (philos->error)
		return ;
	f_mu_lock(mu_start, &philos->error);
}

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
		f_thread(philo, philo_job);
		if (philo->error)
			break ;
		i++;
	}
	if (philo->error)
		philos->error = philo->error;
}

// TODO: check if should do in case of error
void	philos_run_threads(t_philos *philos, pthread_mutex_t *mu_start)
{
	if (philos->error)
		return ;
	f_mu_unlock(mu_start, &philos->error);
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
			pthread_join(philo->tid, NULL);
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
		philos_lock_start(&root.philos, &root.mu.start);
		gettimeofday(&root.philo_param.tv_start, NULL);
		philos_create_threads(&root.philos);
		philos_run_threads(&root.philos, &root.mu.start);
		philos_wait(&root.philos);
	}
	if (root.philos.error)
		root.error = root.philos.error;
	root_cleanup(&root);
	return (root.error);
}
