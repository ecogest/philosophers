/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:11:06 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/01 14:08:39 by mjacq            ###   ########.fr       */
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
		philo_do(philo, taking_rfork);
		philo_do(philo, taking_lfork);
	}
	else
	{
		philo_do(philo, taking_lfork);
		philo_do(philo, taking_rfork);
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
	{
		f_mu_lock(fork, &philo->error);
		if (!philo->error)
		{
			if (philo->activity.type == taking_lfork)
				philo->forks.left_taken = 1;
			else
				philo->forks.right_taken = 1;
		}
	}
	else
		f_puterr_safe("Missing fork.", &philo->mu_output->stderr);
}

void	philo_replace_forks(t_philo *philo)
{
	if (philo->forks.left_taken)
	{
		pthread_mutex_unlock(&philo->forks.left);
		philo->forks.left_taken = 0;
	}
	if (philo->forks.right_taken)
	{
		pthread_mutex_unlock(philo->forks.right);
		philo->forks.right_taken = 0;
	}
}
