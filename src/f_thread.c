/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_thread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:49:07 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/30 17:38:28 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	f_thread(t_philo *philo, void *(*job)(void *), t_error *error)
{
	if (philo->error)
		return ;
	*error = pthread_create(&philo->tid, NULL, job, (void *)philo);
	if (*error)
	{
		f_mu_lock(&philo->mu_output->stderr, &philo->error);
		f_puterr("Failed thread creation.");
		f_mu_unlock(&philo->mu_output->stderr, &philo->error);
	}
}
