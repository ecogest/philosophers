/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_check_and_update.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 16:41:39 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/01 15:18:14 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** @brief Stops if error, 0 hungry philosophers or one dead
*/

bool	status_should_stop(t_philos_status *status)
{
	bool	ret;
	int		err;

	err = pthread_mutex_lock(&status->mu);
	if (!err)
	{
		if (status->hungry_philosphers == 0)
			ret = true;
		else if (status->dead_philosophers)
			ret = true;
		else
			ret = false;
		pthread_mutex_unlock(&status->mu);
		return (ret);
	}
	else
		return (true);
}

/*
** If philo->error or if status_should_stop
*/

bool	philo_should_stop(t_philo *philo)
{
	if (philo->error)
	{
		status_update(philo->status, error_occured);
		return (true);
	}
	else
		return (status_should_stop(philo->status));
}

/*
** events: error_occured, sated, dead
*/

void	status_update(t_philos_status *status, t_status_update update)
{
	t_error	err;

	err = pthread_mutex_lock(&status->mu);
	if (!err)
	{
		if (update == error_occured)
			status->error = error;
		else if (update == sated && status->hungry_philosphers > 0)
			status->hungry_philosphers--;
		else if (update == dead)
			status->dead_philosophers++;
		pthread_mutex_unlock(&status->mu);
	}
}

void	philo_update_status(t_philo *philo, t_status_update update)
{
	status_update(philo->status, update);
}
