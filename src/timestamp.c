/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 11:41:17 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/02 11:38:37 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static uint	f_tv_to_timestamp(struct timeval *now, struct timeval *start)
{
	struct timeval	diff;

	diff.tv_sec = now->tv_sec - start->tv_sec;
	diff.tv_usec = now->tv_usec - start->tv_usec;
	return (diff.tv_sec * 1000 + diff.tv_usec / 1000);
}

uint	f_timestamp_get(void)
{
	static bool				first_start;
	static struct timeval	tv_start;
	struct timeval			tv;

	if (!first_start)
	{
		gettimeofday(&tv_start, NULL);
		first_start = true;
	}
	gettimeofday(&tv, NULL);
	return (f_tv_to_timestamp(&tv, &tv_start));
}
