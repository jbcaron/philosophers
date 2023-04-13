/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:11:41 by jcaron            #+#    #+#             */
/*   Updated: 2023/04/13 12:55:17 by jcaron           ###   ########.fr       */
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

typedef struct	s_event
{
	uint32_t		philo_id;
	enum e_event	type;
	uint64_t		timestamp;
}	t_event;

typedef struct	s_event_buffer
{
	t_event			*events;
	size_t			size;
	size_t			head;
	size_t			tail;
	pthread_mutex_t	lock;
	int				(*push)(struct s_event_buffer *, t_event *);
	bool			(*__pull)(struct s_event_buffer *, t_event *);
	void			(*flush)(struct s_event_buffer *);
}	t_event_buffer;

#endif
