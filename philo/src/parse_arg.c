/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:14:28 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/01 15:08:17 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "utils.h"
#include "simulation.h"

#define ARG_MAX "100000000"

static bool	is_valid_arg(char *arg)
{
	if (!ft_str_is_digit(arg))
		return (false);
	if (arg[0] == '0')
		return (false);
	if (ft_strlen(arg) > ft_strlen(ARG_MAX))
		return (false);
	if (ft_strlen(arg) == (ft_strlen(ARG_MAX)) && ft_strcmp(arg, ARG_MAX))
		return (false);
	return (true);
}

int	get_param(t_settings *param, int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	i = 0;
	while (++i < argc)
	{
		if (is_valid_arg(argv[i]))
			return (EXIT_FAILURE);
	}
	param->nb_philo = itoint32(argv[1]);
	param->time_to_die = itoint32(argv[2]);
	param->time_to_eat = itoint32(argv[3]);
	param->time_to_sleep = itoint32(argv[4]);
	if (argc > 5)
		param->nb_meal = itoint32(argv[5]);
	else
		param->nb_meal = -1;
	return (EXIT_SUCCESS);
}
