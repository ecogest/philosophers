/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_thread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:49:07 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/30 10:56:43 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	f_thread(t_philo *philo, void *(*job)(void *))
{
	if (philo->error)
		return ;
	philo->error = pthread_create(&philo->tid, NULL, job, (void *)philo);
	if (philo->error)
		f_puterr("Failed thread creation.");
}
