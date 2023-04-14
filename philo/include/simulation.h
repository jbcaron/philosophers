/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:11:52 by jcaron            #+#    #+#             */
/*   Updated: 2023/04/14 16:50:46 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include <stdint.h>
# include <pthread.h>
# include "event.h"

typedef enum e_simu
{
	WAIT,
	START,
	STOP
}	t_simu;

typedef enum e_parity
{
	ODD,
	PEER
}	t_parity;

typedef struct s_settings
{
	int32_t			nb_philo;
	int32_t			time_to_die;
	int32_t			time_to_eat;
	int32_t			time_to_sleep;
	int32_t			nb_meal;
}	t_settings;

typedef struct s_prog
{
	t_settings		param;
	uint64_t		start_time;
	t_event_buffer	event_buf;
	t_simu			_state;
	pthread_mutex_t	_lock_state;
	t_simu			(*get_state)(struct s_prog *);
	void			(*set_state)(struct s_prog *, t_simu);
}	t_prog;

typedef struct s_monitoring
{
	t_prog			prog;
	pthread_t		*threads;
	t_philo			*philos;
	pthread_mutex_t	*forks;

}	t_monitoring;

typedef struct s_data_thread
{
	t_philo	*philo;
	t_prog	*prog;
}	t_data_thread;

void	init_prog(t_prog *this, t_settings param);

#endif
