/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:58:24 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/01 15:10:02 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include "utils.h"

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

int	ft_strcmp(const char *s1, const char *s2)
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

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n' || \
			c == '\r' || c == '\t' || c == '\v');
}

bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

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

int32_t	atoint32(const char *str)
{
	int		i;
	int32_t	nb;
	int		sign;

	if (!str)
		return (0);
	i = 0;
	nb = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * sign);
}

uint64_t	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

uint64_t	get_time_us(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}
