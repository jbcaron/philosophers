/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:11:41 by jcaron            #+#    #+#             */
/*   Updated: 2023/04/11 10:12:58 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

enum	e_event
{
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}

typedef struct	s_event
{
	pthread_mutex_t lock;
	int				philo_id;
	enum e_event	event_type;
	uint64_t		timestamp;
}	t_event;

typedef struct	s_event_buffer
{
	t_event			*buffer;
	size_t			size;
	size_t			head;
	size_t			tail;
	pthread_mutex_t	lock;
	
}	t_event_buffer;

#endif
