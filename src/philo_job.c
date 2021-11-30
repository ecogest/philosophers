/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:09:51 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/30 12:27:29 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_get_time(t_philo *philo)
{
	struct timeval	tv;

	if (philo->error)
		return ;
	philo->error = gettimeofday(&tv, NULL);
	philo->state.timestamp = f_tv_to_timestamp(&tv, &philo->param->tv_start);
}

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

void	philo_do(t_philo *philo, t_action action)
{
	int	duration;

	if (philo->error)
		return ;
	philo->state.action = action;
	if (action == taking_lfork || action == taking_rfork)
		philo_take_fork(philo);
	philo_get_time(philo);
	philo_print_action(philo);
	duration = action_get_duration(action, philo->param);
	if (duration)
		f_ms_sleep(duration);
	if (action == eating)
		philo_replace_forks(philo);
}

void	philo_cycle(t_philo *philo)
{
	philo_do(philo, taking_lfork);
	philo_do(philo, taking_rfork);
	philo_do(philo, eating);
	philo->meal_count++;
	philo_do(philo, sleeping);
	philo_do(philo, thinking);
}

void	*philo_job(void *phil)
{
	t_philo	*philo;

	philo = phil;
	while (philo->meal_count != philo->param->max_meal)
	{
		philo_cycle(philo);
		if (philo->error)
			break ;
	}
	return (NULL);
}
