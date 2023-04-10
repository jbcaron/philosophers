/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:10:01 by jcaron            #+#    #+#             */
/*   Updated: 2023/01/15 17:42:40 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "ft_split.h"
#include "ft_malloc.h"

static size_t	count_word(char const *s, char c)
{
	size_t	nb;
	size_t	i;

	nb = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != c && s[i])
			nb++;
		while (s[i] != c && s[i])
			i++;
		while (s[i] == c && s[i])
			i++;
	}
	return (nb);
}

static size_t	len_word(char const *s, char c)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (*s == c && *s)
		s += sizeof(char);
	while (s[len] != c && s[len])
		len++;
	return (len);
}

static size_t	cpy_word(char *dest, char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i] != c && s[i])
	{
		dest[j] = s[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	while (s[i] == c && s[i])
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	size_t	i;

	new = ft_malloc(sizeof(char *) * (count_word(s, c) + 1));
	i = 0;
	if (count_word(s, c) == 0)
	{
		new[i] = NULL;
		return (new);
	}
	while (*s)
	{
		new[i] = ft_malloc(sizeof(char) * (len_word(s, c) + 1));
		s += cpy_word(new[i], s, c);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		ft_free(split[i]);
		i++;
	}
	ft_free(split);
}
