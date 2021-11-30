/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_check_and_update.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 16:41:39 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/30 16:42:38 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_should_stop(t_philo *philo)
{
	bool	ret;

	if (philo->error)
		return (true);
	f_mu_lock(&philo->status->mu, &philo->error);
	if (philo->status->hungry_philosphers == 0)
		ret = true;
	else if (philo->status->dead_philosophers)
		ret = true;
	else
		ret = false;
	f_mu_unlock(&philo->status->mu, &philo->error);
	return (ret);
}

void	philo_update_status(t_philo *philo, t_status_update update)
{
	f_mu_lock(&philo->status->mu, &philo->error);
	if (philo->error)
		philo->status->error = philo->error;
	else if (update == sated && philo->status->hungry_philosphers > 0)
		philo->status->hungry_philosphers--;
	else if (update == dead)
		philo->status->dead_philosophers++;
	f_mu_unlock(&philo->status->mu, &philo->error);
}
