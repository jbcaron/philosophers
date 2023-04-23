/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:11:52 by jcaron            #+#    #+#             */
/*   Updated: 2023/04/23 14:41:00 by jcaron           ###   ########.fr       */
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
	t_event_buffer	event_buf;
	t_simu			_state;
	pthread_mutex_t	_lock_state;
	t_simu			(*get_state)(struct s_prog *);
	void			(*set_state)(struct s_prog *, t_simu);
}	t_prog;

typedef struct s_monitoring
{
	t_prog			prog;
	uint64_t		start_time;
	pthread_t		*threads;
	t_philo			*philos;
	t_snap			*snap_philos;
	pthread_mutex_t	*forks;
	int				(*start)(struct s_monitoring *);
	void			(*maj_snap)(struct s_monitoring *);
	void			(*stop)(struct s_monitoring *);

}	t_monitoring;

typedef struct s_data_thread
{
	t_philo	*philo;
	t_prog	*prog;
}	t_data_thread;

int		_init_monitor_memory(t_monitoring *this);
int		_init_monitor_mutex(t_monitoring *this);
int		_init_prog(t_prog *this, t_settings param);
void	_destroy_monitor_memory(t_monitoring *this);
void	_destroy_monitor_mutex(t_monitoring *this);
void	_destroy_prog(t_prog *this);
int		_start_monitor(t_monitoring *this);
bool	_one_dead_monitor(t_monitoring *this);
void	_maj_snap(t_monitoring *this);

int		init_monitor(t_monitoring *this, t_settings param);
void	destroy_monitor(t_monitoring *this);
void	give_permission_eat(t_monitoring *this);


#endif
