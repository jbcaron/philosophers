/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_num_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:23:15 by jcaron            #+#    #+#             */
/*   Updated: 2023/01/10 11:52:55 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_is_num_alpha.h"

bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	ft_islower(char c)
{
	return (c >= 'a' && c <= 'z');
}

bool	ft_isupper(char c)
{
	return (c >= 'A' && c <= 'Z');
}

bool	ft_isalpha(char c)
{
	return (ft_islower(c) || ft_isupper(c));
}

bool	ft_isalnum(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
