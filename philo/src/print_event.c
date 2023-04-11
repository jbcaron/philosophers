/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:52:40 by jcaron            #+#    #+#             */
/*   Updated: 2023/04/11 10:13:14 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event.h"

void	event_buffer_create(t_print_buffer *buf, size_t size)
{	
	if (pthread_mutex_init(&buf->lock, NULL) < 0)
		return (-1);
	buf->buffer = ft_malloc(size);
	buf->size = size;
	buf->head = 0;
	buf->tail = 0;
}

int	event_buffer_destroy(t_print_buffer *buf)
{
	ft_free(buf->buffer);
	buf->buffer = NULL;
	buf->size = 0;
	buf->head = 0;
	buf->tail = 0;
}

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

void	add_event(s_event)
void	remove_event(s_event)

