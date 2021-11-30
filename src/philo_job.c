/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:09:51 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/30 10:18:26 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_get_time(t_philo *philo)
{
	struct timeval	tv;
	struct timeval	diff;

	gettimeofday(&tv, NULL);
	diff.tv_sec = tv.tv_sec - philo->param->tv_start.tv_sec;
	diff.tv_usec = tv.tv_usec - philo->param->tv_start.tv_usec;
	philo->state.timestamp = diff.tv_sec * 1000 + diff.tv_usec / 1000;
}

void	philo_print_action(t_philo *philo)
{
	int								i;
	static const t_action_display	actions[5] = {\
	{.action = eating, .color = "\e[33m", .stract = "is eating"}, \
	{.action = sleeping, .color = "\e[34m", .stract = "is sleeping"}, \
	{.action = thinking, .color = "\e[35m", .stract = "is thinking"}, \
	{.action = taking_fork, .color = "\e[32m", .stract = "has taken a fork"}, \
	{.action = died, .color = "\e[31m", .stract = "died"} \
	};

	i = 0;
	while (philo->state.action != actions[i].action)
		i++;
	f_mu_lock(philo->mu_stdout, &philo->error);
	if (philo->error)
		return ;
	printf("\e[38m%u\e[0m \e[1m%ld\e[0m %s%s\e[0m\n", philo->state.timestamp, \
			philo->tid, actions[i].color, actions[i].stract);
	f_mu_unlock(philo->mu_stdout, &philo->error);
}

void	philo_do(t_philo *philo, t_action action)
{
	philo->state.action = action;
	philo_get_time(philo);
	philo_print_action(philo);
	usleep(philo->param->tt_sleep * 1000);
}

void	philo_cycle(t_philo *philo)
{
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
