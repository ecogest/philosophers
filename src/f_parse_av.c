/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parse_av.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:58:20 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/29 11:58:53 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	has_enough_args(int ac)
{
	return (ac == 5 || ac == 6);
}

static bool	all_args_positive_integers(const char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!ft_isint(av[i]) || ft_atoi(av[i]) < 0)
			return (false);
		i++;
	}
	return (true);
}

static bool	philo_count_strictly_positive(const char *philo_count)
{
	return (ft_atoi(philo_count) > 0);
}

static t_error	args_check_error(int ac, const char **av, const char **err)
{
	*err = NULL;
	if (!has_enough_args(ac))
		*err = "Wrong number of arguments.";
	else if (!all_args_positive_integers(av))
		*err = "Arguments should be positive integers.";
	else if (!philo_count_strictly_positive(av[1]))
		*err = "The number of philosophers should be strictly positive.";
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
	const char	*err_msg;

	*all = (t_all){.philo_param.max_meal = -1};
	all->error = args_check_error(ac, av, &err_msg);
	if (!all->error)
	{
		all->philos.philo_count = ft_atoi(av[1]);
		all->philo_param.tt_die = ft_atoi(av[2]);
		all->philo_param.tt_eat = ft_atoi(av[3]);
		all->philo_param.tt_sleep = ft_atoi(av[4]);
		if (ac == 6)
			all->philo_param.max_meal = ft_atoi(av[5]);
		printf("philos: %d\nttd: %d\ntte: %d\ntts:%d\nmax meals: %d\n", \
				all->philos.philo_count, \
				all->philo_param.tt_die, all->philo_param.tt_eat, \
				all->philo_param.tt_sleep, all->philo_param.max_meal);
	}
	else
	{
		f_puterr(err_msg);
		f_usage();
	}
}
