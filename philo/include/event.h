/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:11:41 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/02 13:24:25 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>
# include <pthread.h>

enum	e_event
{
	TAKE_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

typedef struct s_event
{
	uint64_t		timestamp;
	uint32_t		philo_id;
	enum e_event	type;
}	t_event;

typedef struct s_event_buffer
{
	struct s_event	*_events;
	size_t			_size;
	size_t			_head;
	size_t			_tail;
	pthread_mutex_t	_lock;
	int				(*push)(struct s_event_buffer *, t_event *);
	bool			(*_pull)(struct s_event_buffer *, t_event *);
	void			(*flush)(struct s_event_buffer *, uint64_t);
}	t_event_buffer;

int		init_event_buffer(t_event_buffer *this, size_t size);
void	destroy_event_buffer(t_event_buffer *this);
bool	push_event_buffer(t_event_buffer *this, t_event	*event);
bool	pull_event_buffer(t_event_buffer *this, t_event	*event);
void	flush_event_buffer(t_event_buffer *this, uint64_t start_time);

#endif
