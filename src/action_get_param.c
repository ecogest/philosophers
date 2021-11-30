/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_get_param.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 11:48:26 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/30 12:07:08 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	action_get_duration(t_action action, t_philo_param *param)
{
	if (action == sleeping)
		return (param->tt_sleep);
	else if (action == eating)
		return (param->tt_eat);
	else if (action == died)
		return (param->tt_die);
	else
		return (0);
}

t_act_d	action_get_display(t_action action)
{
	int						i;
	static const t_act_d	actions[] = {\
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
