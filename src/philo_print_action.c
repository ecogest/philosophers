/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print_action.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:39:49 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/30 11:51:14 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print_action(t_philo *philo)
{
	t_act_d	display;

	if (philo->error)
		return ;
	display = action_get_display(philo->state.action);
	f_mu_lock(philo->mu_stdout, &philo->error);
	if (philo->error)
		return ;
	printf("\e[38m%u\e[0m \e[1m%d\e[0m %s%s\e[0m\n", philo->state.timestamp, \
			philo->id, display.color, display.stract);
	f_mu_unlock(philo->mu_stdout, &philo->error);
}
