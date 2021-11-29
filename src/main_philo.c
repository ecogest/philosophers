/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:24:29 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/29 13:58:04 by mjacq            ###   ########.fr       */
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

void	root_init(t_root *root)
{
	*root = (t_root){.philo_param.max_meal = -1};
	f_mutex_init(&root->mu_stdout, &root->error);
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
		philos_create_threads(&root.philos);
		philos_run_threads(&root.philos);
		if (root.philos.error)
			root.error = root.philos.error;
	}
	root_cleanup(&root);
	return (root.error);
}
