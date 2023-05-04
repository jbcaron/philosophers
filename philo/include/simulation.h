/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:11:52 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/04 16:52:55 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include <stdint.h>
# include <pthread.h>
# include "event.h"

struct	s_philo;

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
	struct s_settings		param;
	struct s_event_buffer	event_buf;
	pthread_mutex_t			_lock_state;
	t_simu					(*get_state)(struct s_prog *);
	void					(*set_state)(struct s_prog *, t_simu);
	uint64_t				start_time;
	enum e_simu				_state;
}	t_prog;

typedef struct s_monitoring
{
	struct s_prog		prog;
	struct s_philo		*philos;
	struct s_snap_philo	*snap_philos;
	pthread_t			*threads;
	pthread_mutex_t		*forks;
	int					(*start)(struct s_monitoring *);
	void				(*maj_snap)(struct s_monitoring *);
	bool				(*one_dead)(struct s_monitoring *);
	bool				(*all_eat)(struct s_monitoring *);
	void				(*stop)(struct s_monitoring *);
}	t_monitoring;

int		_init_monitor_memory(struct s_monitoring *this);
int		_init_monitor_mutex(struct s_monitoring *this);
int		_init_prog(struct s_prog *this, struct s_settings param);
int		_init_monitor_philo(t_monitoring *this);
void	_destroy_monitor_memory(struct s_monitoring *this);
void	_destroy_monitor_mutex(struct s_monitoring *this);
void	_destroy_prog(struct s_prog *this);
int		_start_monitor(struct s_monitoring *this);
void	_stop_monitor(t_monitoring *this);
bool	_one_dead_monitor(struct s_monitoring *this);
bool	_all_eat_enought(t_monitoring *this);
void	_maj_snap(struct s_monitoring *this);

int		init_monitor(struct s_monitoring *this, t_settings param);
void	destroy_monitor(struct s_monitoring *this);
t_simu	_get_state_simu(t_prog *this);
void	_set_state_simu(t_prog *this, t_simu state);
void	give_permission_eat(struct s_monitoring *this);

int		get_param(struct s_settings *param, int argc, char **argv);

#endif
