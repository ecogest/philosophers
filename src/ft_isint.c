/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:00:59 by mjacq             #+#    #+#             */
/*   Updated: 2021/12/02 18:19:52 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int	ft_isint(const char *str)
{
	long	number;
	int		sign;

	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (0);
	number = 0;
	while (*str >= '0' && *str <= '9')
	{
		number = 10 * number + *str++ - '0';
		if (sign * number > INT_MAX || sign * number < INT_MIN)
			return (0);
	}
	if (*str)
		return (0);
	return (1);
}
