/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:23:15 by jcaron            #+#    #+#             */
/*   Updated: 2023/01/15 17:47:57 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_bzero.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char		*s_char;
	unsigned long		*s_long;

	if (!s)
		return ;
	s_char = (unsigned char *)s;
	while (n % sizeof(unsigned long))
	{
		*(s_char++) = 0;
		n--;
	}
	s_long = (unsigned long *)s_char;
	while (n / sizeof(unsigned long))
	{
		*(s_long++) = 0;
		n -= sizeof(unsigned long);
	}
	s_char = (unsigned char *)s_long;
	while (n)
	{
		*(s_char++) = 0;
		n--;
	}
	return ;
}
