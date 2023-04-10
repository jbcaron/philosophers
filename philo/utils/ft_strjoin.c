/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:10:12 by jcaron            #+#    #+#             */
/*   Updated: 2023/01/15 17:46:55 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strjoin.h"
#include "ft_str.h"
#include "ft_malloc.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;

	new = ft_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	ft_strcpy(new, s1);
	ft_strcpy(new + sizeof(char) * ft_strlen(s1), s2);
	new[sizeof(char) * (ft_strlen(s1) + ft_strlen(s2))] = '\0';
	return (new);
}
