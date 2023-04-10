/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:29:21 by jcaron            #+#    #+#             */
/*   Updated: 2023/03/11 23:54:42 by jcaron           ###   ########.fr       */
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
#include <stdbool.h>
#include "ft_malloc.h"

/**
 * @brief Pointer to the last allocated node.
 *
 * This static variable holds a pointer to the last allocated node. It is used
 * to keep track of all allocated memory and to facilitate deallocation.
**/

t_malloc_node	*get_last_node(t_malloc_node *node, bool push)
{
	static t_malloc_node	*last_node = NULL;

	if (push)
		last_node = node;
	return (last_node);
}

int	ft_mem_bucket(int ac_bucket)
{
	static int	bucket = 0;

	if (ac_bucket < 0)
		return (bucket);
	else
		bucket = ac_bucket;
	return (bucket);
}

/**
 * @brief Adds a node to the list of allocated nodes.
 *
 * This function adds a node to the list of allocated nodes, updating the
 * pointers of the previous and next nodes as necessary.
 * 
 * @param node Pointer to the node to add to the list.
**/

void	ft_malloc_node_add(t_malloc_node *node, size_t size)
{
	t_malloc_node	*last_node;

	last_node = get_last_node(NULL, false);
	if (last_node)
		last_node->next = node;
	node->bucket = ft_mem_bucket(-1);
	node->size = size;
	node->prev = get_last_node(NULL, false);
	node->next = NULL;
	get_last_node(node, true);
	return ;
}

/**
 * @brief Removes a node from the list of allocated nodes.
 *
 * This function removes a node from the list of allocated nodes, updating the
 * pointers of the previous and next nodes as necessary.
 *
 * @param node Pointer to the node to remove from the list.
**/

void	ft_malloc_node_del(t_malloc_node *node)
{
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	else
		get_last_node(node->prev, true);
}

/**
 * @brief Frees all allocated memory.
 *
 * This function frees all previously allocated memory, removing all nodes from
 * the list of allocated nodes.
**/

void	ft_free_all(void)
{
	t_malloc_node	*tmp;
	t_malloc_node	*prev;

	tmp = get_last_node(NULL, false);
	while (tmp)
	{
		prev = tmp->prev;
		free(tmp);
		tmp = prev;
	}
}
