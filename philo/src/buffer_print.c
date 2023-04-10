/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:03:32 by jcaron            #+#    #+#             */
/*   Updated: 2023/04/03 11:18:19 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <pthread.h>
#include "utils.h"

typedef struct	s_print_buffer
{
	char			*buffer;
	size_t			size;
	size_t			head;
	size_t			tail;
	pthread_mutex_t	lock;
}	t_print_buffer;

void	print_buffer_create(t_print_buffer *buf, size_t size)
{
	buf->buffer = ft_malloc(size);
	buf->size = size;
	buf->head = 0;
	buf->tail = 0;
}

int	print_buffer_destroy(t_print_buffer *buf)
{
	ft_free(buf->buffer);
	buf->buffer = NULL;
	buf->size = 0;
	buf->head = 0;
	buf->tail = 0;
	if (pthread_mutex_init(&buf->lock, NULL) < 0)
		return (-1);
}

/**
 * @brief Writes a string message to a print buffer.
 *
 * @param buf A pointer to the print buffer.
 * @param msg The message to write to the buffer.
 * 
 * @return void
 **/

int	print_buffer_write(t_print_buffer *buf, char *msg)
{
	size_t	i;

	pthread_mutex_lock(&buf->lock);
	while (msg)
	{
		i = (buf->tail + 1) % buf->size;
		while (i == buf->tail)
			;
		buf->buffer[i] = *msg;
		buf->tail = i;
		msg++;
	}
}
