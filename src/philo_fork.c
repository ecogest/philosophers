/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:11:06 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/30 13:11:27 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO: die if fork == NULL
void	philo_take_fork(t_philo *philo)
{
	pthread_mutex_t	*fork;

	if (philo->error)
		return ;
	if (philo->state.action == taking_lfork)
		fork = &philo->forks.left;
	else
		fork = philo->forks.right;
	if (fork)
		f_mu_lock(fork, &philo->error);
	else
		f_puterr("Missing fork.");
}

void	philo_replace_forks(t_philo *philo)
{
	f_mu_unlock(&philo->forks.left, &philo->error);
	if (philo->forks.right)
		f_mu_unlock(philo->forks.right, &philo->error);
}
