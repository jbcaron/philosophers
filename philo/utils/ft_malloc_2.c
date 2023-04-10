/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:29:21 by jcaron            #+#    #+#             */
/*   Updated: 2023/03/14 23:48:43 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_malloc.c
 *
 * @brief Implementations for custom memory management functions.
 *
 * This file contains the implementations for custom memory management functions
 * ft_malloc, ft_free, and ft_free_all. These functions are intended to provide
 * a simple and easy-to-use interface for allocating, freeing, and freeing all
 * dynamically allocated memory.
 *
 * @author jcaron
 *
 * @date January 2023
**/

#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include "ft_malloc.h"
#include "ft_mem.h"
#include <readline/readline.h>
#include <readline/history.h>

/**
 * @brief Allocates memory.
 *
 * This function allocates memory of a specified size, creating a new node to
 * keep track of the allocated memory. If the system is unable to fulfill the
 * request for memory, the function will free all allocated memory and will
 * also write an error message to stderr and exit the program.The user should
 * always use ft_free() function to free the allocated memory
 * 
 * @param size The number of bytes to allocate.
 *
 * @return A pointer to the allocated memory.
**/

void	*ft_malloc(size_t size)
{
	void			*data;
	t_malloc_node	*node;

	node = malloc(size + sizeof(t_malloc_node));
	if (!node)
	{
		write(2, "FATAL ERROR: memory allocation failed", 37);
		rl_clear_history();
		ft_free_all();
		kill(0, SIGKILL);
		exit(1);
	}
	data = (void *)((size_t)node + sizeof(t_malloc_node));
	ft_malloc_node_add(node, size);
	return (data);
}

void	*ft_realloc(void *old_data, size_t size)
{
	t_malloc_node	*old_node;
	void			*new_data;

	if (!old_data)
		return (ft_malloc(size));
	if (size == 0)
	{
		ft_free(old_data);
		return (NULL);
	}
	old_node = (t_malloc_node *)((size_t)old_data - sizeof(t_malloc_node));
	new_data = ft_malloc(size);
	if (size > old_node->size)
		size = old_node->size;
	ft_memcpy(new_data, old_data, size);
	ft_free(old_data);
	return (new_data);
}

void	ft_free(void *data)
{
	t_malloc_node	*node;

	if (!data)
		return ;
	node = (t_malloc_node *)((size_t)data - sizeof(t_malloc_node));
	ft_malloc_node_del(node);
	free (node);
}

void	ft_free_bucket(int bucket)
{
	t_malloc_node	*tmp;
	t_malloc_node	*prev;

	tmp = get_last_node(NULL, false);
	while (tmp)
	{
		prev = tmp->prev;
		if (tmp->bucket == bucket)
		{
			ft_malloc_node_del(tmp);
			free(tmp);
		}
		tmp = prev;
	}
}

size_t	ft_tot_alloc(void)
{
	size_t			total;
	t_malloc_node	*tmp;

	total = 0;
	tmp = get_last_node(NULL, false);
	while (tmp)
	{
		total += tmp->size;
		tmp = tmp->prev;
	}
	return (total);
}
