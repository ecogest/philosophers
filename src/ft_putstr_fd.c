/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:54:34 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/02 18:21:44 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"
/*
** Put a string to a specified file descriptor.
*/

void	ft_putstr_fd(const char *s, int fd)
{
	if (fd == -1 || s == NULL)
		return ;
	write(fd, s, ft_strlen(s));
}
