/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root_parse_av.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:58:20 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/29 14:03:25 by mjacq            ###   ########.fr       */
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

static void
	err_check_av(t_error *err, const char **strerr, int ac, const char **av)
{
	*strerr = NULL;
	*err = success;
	if (!has_enough_args(ac))
		*strerr = "Wrong number of arguments.";
	else if (!all_args_positive_integers(av))
		*strerr = "Arguments should be positive integers.";
	else if (!philo_count_strictly_positive(av[1]))
		*strerr = "The number of philosophers should be strictly positive.";
	else
		return ;
	*err = error_av;
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

void	root_parse_av(t_root *root, int ac, const char **av)
{
	const char	*strerr;

	if (root->error)
		return ;
	err_check_av(&root->error, &strerr, ac, av);
	if (!root->error)
	{
		root->philos.count = ft_atoi(av[1]);
		root->philo_param.tt_die = ft_atoi(av[2]);
		root->philo_param.tt_eat = ft_atoi(av[3]);
		root->philo_param.tt_sleep = ft_atoi(av[4]);
		if (ac == 6)
			root->philo_param.max_meal = ft_atoi(av[5]);
		printf("philos: %d\nttd: %d\ntte: %d\ntts:%d\nmax meals: %d\n", \
				root->philos.count, \
				root->philo_param.tt_die, root->philo_param.tt_eat, \
				root->philo_param.tt_sleep, root->philo_param.max_meal);
	}
	else
	{
		f_puterr(strerr);
		f_put_usage();
	}
}
