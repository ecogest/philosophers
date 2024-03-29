/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_check_and_update.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 16:41:39 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/01 17:54:34 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** @brief Stops if error, 0 hungry philosophers or one dead
*/

bool	status_should_stop(t_philos_state *status)
{
	bool	ret;

	if (status->hungry_philosphers == 0)
		ret = true;
	else if (status->dead_philosophers)
		ret = true;
	else
		ret = false;
	return (ret);
}

/*
** If philo->error or if status_should_stop
*/

bool	philo_should_stop(t_philo *philo)
{
	if (philo->error)
	{
		status_update(philo->philos_state, error_occured);
		return (true);
	}
	else
		return (status_should_stop(philo->philos_state));
}

/*
** events: error_occured, sated, dead
*/

void	status_update(t_philos_state *status, t_status_update update)
{
	if (update == error_occured)
		status->error = error;
	else if (update == sated && status->hungry_philosphers > 0)
		status->hungry_philosphers--;
}

void	philo_update_status(t_philo *philo, t_status_update update)
{
	status_update(philo->philos_state, update);
}
