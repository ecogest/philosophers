/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_malloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:48:38 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/29 12:55:18 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*f_calloc(size_t block_size, size_t count, t_error *error)
{
	void	*mem;

	mem = malloc(block_size * count);
	if (mem == NULL && error != NULL)
		*error = error_malloc;
	return (mem);
}
