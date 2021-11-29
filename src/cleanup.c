/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:42:37 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/29 13:42:48 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_cleanup(t_philos *philos)
{
	free(philos->array);
	philos->array = NULL;
}

void	cleanup(t_all *all)
{
	philos_cleanup(&all->philos);
}
