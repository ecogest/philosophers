/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:11:06 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/30 17:38:25 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** We want the neighbours to compete for the same fork first
** Then the winner can take the second one
** Otherwise every philosopher could end up with only one fork.
*/

void	philo_take_forks(t_philo *philo)
{
	if (philo->error)
		return ;
	if (philo->id % 2)
	{
		philo_do(philo, taking_lfork);
		philo_do(philo, taking_rfork);
	}
	else
	{
		philo_do(philo, taking_rfork);
		philo_do(philo, taking_lfork);
	}
}

// TODO: die if fork == NULL
void	philo_pick_a_fork(t_philo *philo)
{
	pthread_mutex_t	*fork;

	if (philo->error)
		return ;
	if (philo->activity.type == taking_lfork)
		fork = &philo->forks.left;
	else
		fork = philo->forks.right;
	if (fork)
		f_mu_lock(fork, &philo->error);
	else
	{
		f_mu_lock(&philo->mu_output->stderr, &philo->error);
		f_puterr("Missing fork.");
		f_mu_unlock(&philo->mu_output->stderr, &philo->error);
	}
}

void	philo_replace_forks(t_philo *philo)
{
	f_mu_unlock(&philo->forks.left, &philo->error);
	if (philo->forks.right)
		f_mu_unlock(philo->forks.right, &philo->error);
}
