/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parse_av.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:58:20 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/28 18:09:08 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	has_enough_args(int ac)
{
	return (ac == 5 || ac == 6);
}

static bool	all_args_positive_numbers(const char **av)
{
	(void)av;
	return (true);
}

static bool	philo_count_strictly_positive(const char *philo_count)
{
	(void)philo_count;
	return (true);
}

static t_error	perform_checks_on_args(int ac, const char **av)
{
	if (!has_enough_args(ac))
		f_puterr("Wrong number of arguments.");
	else if (!all_args_positive_numbers(av))
		f_puterr("Arguments should be positive numbers (below INT_MAX).");
	else if (!philo_count_strictly_positive(av[1]))
		f_puterr("The number of philosophers should be strictly positive.");
	else
		return (success);
	return (error_av);
}

/*
** Valid input if:
** - between 4 and 5 args (ac == 5 or 6)
** - args are numeric and positive
** - args value < size_t max
** - count of philos is strictly positive
**
** max meal: -1 if not specified
*/

void	f_parse_av(t_all *all, int ac, const char **av)
{
	*all = (t_all){.philo_param.max_meal = -1};
	all->error = perform_checks_on_args(ac, av);
	if (!all->error)
	{
		all->philos.philo_count = ft_atoi(av[1]);
		all->philo_param.tt_die = ft_atoi(av[2]);
		all->philo_param.tt_eat = ft_atoi(av[3]);
		all->philo_param.tt_sleep = ft_atoi(av[4]);
		if (ac == 6)
			all->philo_param.max_meal = ft_atoi(av[5]);
		printf("philos: %d\nttd: %d\ntte: %d\ntts:%d\nmax meals: %d\n",
				all->philos.philo_count,
				all->philo_param.tt_die, all->philo_param.tt_eat,
				all->philo_param.tt_sleep, all->philo_param.max_meal);
	}
}
