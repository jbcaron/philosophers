/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:23:15 by jcaron            #+#    #+#             */
/*   Updated: 2023/01/09 20:32:29 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_to_case.h"
#include "ft_is_num_alpha.h"

int	ft_tolower(char c)
{
	if (ft_isupper(c))
		c += 32;
	return (c);
}

int	ft_toupper(char c)
{
	if (ft_islower(c))
		c -= 32;
	return (c);
}
