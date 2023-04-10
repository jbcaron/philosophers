/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:40:40 by jcaron            #+#    #+#             */
/*   Updated: 2023/03/12 14:42:54 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_str_is.h"
#include "ft_is_num_alpha.h"
#include "ft_str_research.h"
#include "ft_str.h"

bool	ft_str_is_digit(const char *str)
{
	if (!ft_isdigit(*str))
		return (false);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

bool	ft_str_is_int(const char *str)
{
	size_t	len;
	bool	is_neg;

	is_neg = false;
	if (*str == '-')
		is_neg = true;
	if (*str == '-' || *str == '+')
		str++;
	if (!ft_str_is_digit(str))
		return (false);
	len = ft_strlen(str);
	if (len > 10)
		return (false);
	else if (len == 10)
	{
		if (is_neg && ft_strcmp(STR_MIN_INT, str) < 0)
			return (false);
		else if (!is_neg && ft_strcmp(STR_MAX_INT, str) < 0)
			return (false);
	}
	return (true);
}

bool	ft_str_is_long(const char *str)
{
	size_t	len;
	bool	is_neg;

	is_neg = false;
	if (*str == '-')
		is_neg = true;
	if (*str == '-' || *str == '+')
		str++;
	if (!ft_str_is_digit(str))
		return (false);
	len = ft_strlen(str);
	if (len > 19)
		return (false);
	else if (len == 19)
	{
		if (is_neg && ft_strcmp(STR_MIN_LONG, str) < 0)
			return (false);
		else if (!is_neg && ft_strcmp(STR_MAX_LONG, str) < 0)
			return (false);
	}
	return (true);
}
