/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print_action.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:39:49 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/01 11:01:09 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_fmt	action_get_format(t_action action)
{
	int					i;
	static const t_fmt	actions[] = {\
	{.action = eating, .color = "\e[33m", .stract = "is eating"}, \
	{.action = sleeping, .color = "\e[34m", .stract = "is sleeping"}, \
	{.action = thinking, .color = "\e[35m", .stract = "is thinking"}, \
	{.action = taking_lfork, .color = "\e[32m", .stract = "has taken a fork"}, \
	{.action = taking_rfork, .color = "\e[32m", .stract = "has taken a fork"}, \
	{.action = died, .color = "\e[31m", .stract = "died"} \
	};

	i = 0;
	while (action != actions[i].action)
		i++;
	return (actions[i]);
}

static int	print_action_safe(uint start, int id, t_fmt *fmt, \
		pthread_mutex_t *mu_stdout)
{
	int		err;

	err = pthread_mutex_lock(mu_stdout);
	if (!err)
	{
		printf("\e[38m%u\e[0m \e[1m%d\e[0m %s%s\e[0m\n", \
				start, id, fmt->color, fmt->stract);
		err = pthread_mutex_unlock(mu_stdout);
	}
	return (err);
}

void	philo_print_action(t_philo *philo)
{
	t_fmt	fmt;
	int		err;

	if (philo->error)
		return ;
	fmt = action_get_format(philo->activity.type);
	err = print_action_safe(philo->activity.start, philo->id, &fmt, \
			&philo->mu_output->stdout);
	if (err)
		philo->error = err;
}
