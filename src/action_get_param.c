/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_get_param.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 11:48:26 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/01 11:00:28 by mjacq            ###   ########.fr       */
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
