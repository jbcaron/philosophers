/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:52:40 by jcaron            #+#    #+#             */
/*   Updated: 2023/04/14 15:46:21 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "event.h"
#include "error.h"

/**
 * @brief Initializes the event buffer.
 * @param this Pointer to the event buffer structure.
 * @param size Size of the event buffer.
 * @return ERROR_MALLOC if memory allocation fails, ERROR_MUTEX if mutex
 * initialization fails, or SUCCESS if successful.
 */

int	init_event_buffer(t_event_buffer *this, size_t size)
{	
	this->_events = malloc(sizeof(*this->_events) * size);
	if (!this->_events)
		return (ERROR_MALLOC);
	this->_size = size;
	this->_head = 0;
	this->_tail = 0;
	if (pthread_mutex_init(&this->_lock, NULL) < 0)
	{
		free(this->_events);
		return (ERROR_MUTEX);
	}
	return (SUCCESS);
}

/**
 * @brief Destroys the event buffer and releases resources.
 * @param this Pointer to the event buffer structure.
 */

void	destroy_event_buffer(t_event_buffer *this)
{
	ft_free(this->_events);
	pthread_mutex_destroy(&this->_lock);
	this->_events = NULL;
	this->_size = 0;
	this->_head = 0;
	this->_tail = 0;
}

/**
 * @brief Pushes an event into the event buffer.
 * @param this Pointer to the event buffer structure.
 * @param event Pointer to the event structure to be pushed.
 * @return true if the event is pushed successfully; false if the buffer is
 * full.
 */

bool	push_event_buffer(t_event_buffer *this, t_event	*event)
{
	size_t	i;

	pthread_mutex_lock(&this->_lock);
	i = (this->_head + 1) % this->_size;
	if (i == this->_tail)
	{
		pthread_mutex_lock(&this->_lock);
		return (false);
	}
	this->_events[i] = *event;
	this->_tail = i;
	pthread_mutex_lock(&this->_lock);
	return (true);
}

/**
 * @brief Pulls an event from the event buffer.
 * @param this Pointer to the event buffer structure.
 * @param event Pointer to the event structure to store the pulled event.
 * @return true if an event is pulled successfully; false if the buffer is
 * full.
 */

bool	pull_event_buffer(t_event_buffer *this, t_event	*event)
{
	size_t	i;

	pthread_mutex_lock(&this->_lock);
	i = (this->_tail + 1) % this->_size;
	if (i == this->_head)
	{
		pthread_mutex_lock(&this->_lock);
		return (false);
	}
	*event = this->_events[this->_tail];
	this->_tail = (this->_tail + 1) % this->_size;
	pthread_mutex_lock(&this->_lock);
	return (true);
}

static const char	*g_action[] = {
	"has taken a fork",
	"is eating",
	"is sleeping",
	"is thinking",
	"died"
};

/**
 * @brief Flushes the event buffer and prints the events.
 * @param this Pointer to the event buffer structure.
 */

void	flush_event_buffer(t_event_buffer *this)
{
	t_event	event;

	while (this->_pull(this, &event))
	{
		printf("%ld %d %s\n", event.timestamp, event.philo_id,
			g_action[event.type]);
	}
}
