/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print_action.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:39:49 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/30 10:43:14 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_action_display	action_get_display(t_action action)
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
	while (action != actions[i].action)
		i++;
	return (actions[i]);
}

void	philo_print_action(t_philo *philo)
{
	t_action_display	display;

	display = action_get_display(philo->state.action);
	f_mu_lock(philo->mu_stdout, &philo->error);
	if (philo->error)
		return ;
	printf("\e[38m%u\e[0m \e[1m%ld\e[0m %s%s\e[0m\n", philo->state.timestamp, \
			philo->tid, display.color, display.stract);
	f_mu_unlock(philo->mu_stdout, &philo->error);
}
