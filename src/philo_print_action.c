/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print_action.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:39:49 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/02 12:43:47 by mjacq            ###   ########.fr       */
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

void	put_action(uint timestamp, int id, t_action action)
{
	t_fmt	fmt;

	fmt = action_get_format(action);
	printf("\e[38m%u\e[0m \e[1m%d\e[0m %s%s\e[0m\n", \
			timestamp, id, fmt.color, fmt.stract);
}

int	mu_put_action(uint timestamp, int id, t_action action, \
		pthread_mutex_t *mu_stdout)
{
	int		err;

	err = pthread_mutex_lock(mu_stdout);
	if (!err)
	{
		put_action(timestamp, id, action);
		err = pthread_mutex_unlock(mu_stdout);
	}
	return (err);
}

void	philo_put_action(t_philo *philo)
{
	int		err;

	if (philo->error)
		return ;
	err = pthread_mutex_lock(&philo->mu_output->stdout);
	if (!err)
	{
		philo_timestamp_start(philo);
		if (!philo_should_stop(philo))
		{
			put_action(philo->activity.start, philo->id, philo->activity.type);
		}
		pthread_mutex_unlock(&philo->mu_output->stdout);
	}
	if (err)
		philo->error = err;
}
