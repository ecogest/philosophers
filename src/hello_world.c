/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hello_world.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:16:38 by mjacq             #+#    #+#             */
/*   Updated: 2021/04/18 19:07:32 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hello_world.h"
#include <unistd.h>

int	hello_world(void)
{
	write(1, "Hello world!\n", 13);
	return (0);
}
