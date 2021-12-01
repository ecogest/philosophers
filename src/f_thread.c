/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_thread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:49:07 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/01 10:24:20 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	f_thread(t_philo *philo, void *(*job)(void *), t_error *error)
{
	if (philo->error)
		return ;
	*error = pthread_create(&philo->tid, NULL, job, (void *)philo);
	if (*error)
		f_puterr_safe("Failed thread creation.", &philo->mu_output->stderr);
}
