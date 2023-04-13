/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:52:40 by jcaron            #+#    #+#             */
/*   Updated: 2023/04/13 11:37:18 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "event.h"
#include "error.h"

int	init_event_buffer(t_event_buffer *this, size_t size)
{	
	this->events = malloc(sizeof(*this->events) * size);
	if (!this->events)
		return (ERROR_MALLOC);
	this->size = size;
	this->head = 0;
	this->tail = 0;
	if (pthread_mutex_init(&this->lock, NULL) < 0)
	{
		free(this->events);
		return (ERROR_MUTEX);
	}
	return (SUCCESS);
}

void	destroy_event_buffer(t_event_buffer *this)
{
	ft_free(this->events);
	pthread_mutex_destroy(&this->lock);
	this->events = NULL;
	this->size = 0;
	this->head = 0;
	this->tail = 0;
}

bool	push_event_buffer(t_event_buffer *this, t_event	*event)
{
	size_t	i;

	pthread_mutex_lock(&this->lock);
	i = (this->head + 1) % this->size;
	if (i == this->tail)
	{
		pthread_mutex_lock(&this->lock);
		return (false);
	}
	this->events[i] = *event;
	this->tail = i;
	pthread_mutex_lock(&this->lock);
	return (true);
}

bool	pull_event_buffer(t_event_buffer *this, t_event	*event)
{
	size_t	i;

	pthread_mutex_lock(&this->lock);
	i = (this->tail + 1) % this->size;
	if (this->head == this->tail)
	{
		pthread_mutex_lock(&this->lock);
		return (false);
	}
	*event = this->events[this->tail];
	this->tail = (this->tail + 1) % this->size;
	pthread_mutex_lock(&this->lock);
	return (true);
}

static const char	*g_action[] = {
	"has taken a fork",
	"is eating",
	"is sleeping",
	"is thinking",
	"died"
};

void	flush_event_buffer(t_event_buffer *this)
{
	t_event	event;

	while (this->__pull(this, &event))
	{
		printf("%ld %d %s\n", event.timestamp, event.philo_id,
			g_action[event.event_type]);
	}
}
