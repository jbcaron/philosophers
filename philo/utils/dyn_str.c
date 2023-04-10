/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:05:28 by jcaron            #+#    #+#             */
/*   Updated: 2023/03/12 18:26:37 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file dyn_str.has
 * 
 * @brief Dynamic string library
 *
 * @author jcaron
 * 
 * @date January 2023
 * 
 * This library provides functions for creating and manipulating dynamic
 * strings, which are strings that can grow or shrink as needed, stored in a
 * contiguous block of memory. A dynamic string is represented by a t_dyn_str
 * structure, which contains the following fields:
 *     char *str: Pointer to the string buffer.
 *     size_t len: Length of the string (not including the null terminator).
 *     size_t capacity: Capacity of the string buffer (number of characters
 *                      that can be stored without reallocating the buffer).
 * The functions provided by the library allow creating and destroying dynamic
 * strings, ensuring that they have enough capacity to hold a given number of
 * additional characters, and appending characters and strings to them.
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dyn_str.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "get_closer_pow.h"
#include "ft_malloc.h"

/**
 * @brief Create a new dynamic string.
 *
 * @param capacity Initial capacity of the string buffer.
 *
 * @return Pointer to the new dynamic string.
*/

t_dyn_str	*ds_create(size_t capacity)
{
	t_dyn_str	*ds;
	size_t		size;

	size = get_closer_pow(capacity + 1);
	ds = ft_malloc(sizeof(*ds));
	ds->str = ft_malloc(sizeof(*ds->str) * (size));
	ds->str[0] = '\0';
	ds->len = 0;
	ds->capacity = size - 1;
	return (ds);
}

/**
 * @brief Destroy a dynamic string.
 *
 * @param ds Pointer to the dynamic string to destroy.
*/

void	ds_destroy(t_dyn_str *ds)
{
	ft_free(ds->str);
	ft_free(ds);
}

/**
 * @brief Ensure that a dynamic string has enough capacity to hold a given
 * number of additional characters.If the string does not have enough capacity,
 * its buffer is reallocated to a larger size.
 *
 * @param ds Pointer to the dynamic string.
 * @param add_len Number of additional characters the string must be able to
 * hold.
*/

static void	ds_ensure_capacity(t_dyn_str *ds, size_t add_len)
{
	char	*new_str;
	size_t	new_size;

	if (ds->len + add_len <= ds->capacity)
		return ;
	new_size = get_closer_pow(ds->len + add_len + 1);
	new_str = ft_malloc(sizeof(*new_str) * new_size);
	ft_memcpy(new_str, ds->str, ds->len + 1);
	ft_free(ds->str);
	ds->str = new_str;
	ds->capacity = new_size - 1;
}

/**
 * @brief Append a character to the end of a dynamic string.
 *
 * @param ds Pointer to the dynamic string.
 * @param c Character to append.
 *
 * @return Number of characters appended (1).
*/

size_t	ds_append_char(t_dyn_str *ds, char c)
{
	ds_ensure_capacity(ds, 1);
	ds->str[ds->len++] = c;
	ds->str[ds->len] = '\0';
	return (1);
}

/**
 * @brief Append a string to the end of a dynamic string.
 * 
 * @param ds Pointer to the dynamic string.
 * @param str String to append.
 *
 * @return Number of characters appended (0 if the input string is NULL).
*/

size_t	ds_append_str(t_dyn_str *ds, char *str)
{
	size_t	add_len;

	if (!str)
		return (0);
	add_len = ft_strlen(str);
	ds_ensure_capacity(ds, add_len);
	ft_memcpy(&ds->str[ds->len], str, add_len + 1);
	ds->len += add_len;
	return (add_len);
}
