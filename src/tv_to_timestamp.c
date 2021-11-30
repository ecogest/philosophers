/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tv_to_timestamp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 11:41:17 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/30 11:44:37 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint	f_tv_to_timestamp(struct timeval *now, struct timeval *start)
{
	struct timeval	diff;

	diff.tv_sec = now->tv_sec - start->tv_sec;
	diff.tv_usec = now->tv_usec - start->tv_usec;
	return (diff.tv_sec * 1000 + diff.tv_usec / 1000);
}
