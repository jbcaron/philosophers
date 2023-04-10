/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:23:15 by jcaron            #+#    #+#             */
/*   Updated: 2023/01/15 17:46:16 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_calloc.h"
#include "ft_bzero.h"
#include "ft_malloc.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = ft_malloc(nmemb * size);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
