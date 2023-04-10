/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:23:15 by jcaron            #+#    #+#             */
/*   Updated: 2023/01/10 12:13:05 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_is_special.h"

bool	ft_isascii(char c)
{
	return (c >= 0);
}

bool	ft_isprint(char c)
{
	return (c >= 32 && c <= 126);
}

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n' || \
			c == '\r' || c == '\t' || c == '\v');
}
