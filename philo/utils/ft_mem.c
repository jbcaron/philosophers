/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:23:15 by jcaron            #+#    #+#             */
/*   Updated: 2023/02/26 15:04:53 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include "ft_mem.h"

void	*ft_memchr(const void *str, unsigned char c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	if (!str)
		return (0);
	ptr = (unsigned char *)str;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return (&ptr[i]);
		i++;
	}
	return (0);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	const uint8_t	*ptr1;
	const uint8_t	*ptr2;

	if (!s1 || !s2)
		return (0);
	i = 0;
	ptr1 = (const uint8_t *)s1;
	ptr2 = (const uint8_t *)s2;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	uint8_t			*dest_u8;
	const uint8_t	*src_u8;
	uint64_t		*dest_u64;
	const uint64_t	*src_u64;

	dest_u64 = (uint64_t *)dest;
	src_u64 = (const uint64_t *)src;
	if (!dest || !src)
		return (NULL);
	if ((size_t)src % 8 == 0 && (size_t)dest % 8 == 0)
	{
		while (n / 8)
		{
			*dest_u64++ = *src_u64++;
			n -= 8;
		}
	}
	dest_u8 = (uint8_t *)dest_u64;
	src_u8 = (const uint8_t *)src_u64;
	while (n)
	{
		*dest_u8++ = *src_u8++;
		n--;
	}
	return (dest);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	uint8_t	*ptr;

	if (!s)
		return (NULL);
	i = 0;
	ptr = s;
	while (i < n)
	{
		ptr[i] = (uint8_t)c;
		i++;
	}
	return (s);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	ssize_t			i;
	uint8_t			*dest_u8;
	const uint8_t	*src_u8;

	if (dest <= src)
		ft_memcpy(dest, src, n);
	else
	{
		i = n - 1;
		dest_u8 = (uint8_t *)dest;
		src_u8 = (const uint8_t *)src;
		while (i >= 0)
		{
			dest_u8[i] = src_u8[i];
			i--;
		}
	}
	return (dest);
}
