/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:31:04 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/29 14:31:20 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** @brief default params (max_meal = -1) + stdout mutex init
*/

void	root_init(t_root *root)
{
	*root = (t_root){.philo_param.max_meal = -1};
	f_mutex_init(&root->mu_stdout, &root->error);
}