/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:14:28 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/01 12:47:48 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "simulation.h"

#define ARG_MAX "100000000"

static size_t	ft_strlen(const char *str)
{
	const char		*start;
	const uint64_t	*str_long;

	start = str;
	if (!str)
		return (0);
	while ((size_t)str % sizeof(uint64_t) && *str)
		++str;
	str_long = (const uint64_t *)str;
	while ((((uint64_t)str_long - 0x0101010101010101u)
			& ~(uint64_t)str_long & 0x8080808080808080u) == 0)
		str_long += sizeof(uint64_t);
	str = (const char *)str_long;
	while (*str)
		++str;
	return ((size_t)(str - start));
}

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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
