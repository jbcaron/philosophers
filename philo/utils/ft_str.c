/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:23:15 by jcaron            #+#    #+#             */
/*   Updated: 2023/02/06 13:40:15 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_malloc.h"

size_t	ft_strlen(const char *str)
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

char	*ft_strcpy(char *dest, const char *src)
{
	if (!dest || !src)
		return (NULL);
	ft_memcpy(dest, src, ft_strlen(src) + 1);
	return (dest);
}

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!dest || !src)
		return (NULL);
	while (dest[i])
		i++;
	while (j < n)
	{
		dest[i + j] = src [j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = ft_malloc(sizeof(char) * (len + 1));
	ft_memcpy(dup, s, len + 1);
	return (dup);
}

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
