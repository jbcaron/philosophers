/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:11:52 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/01 15:28:11 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include <stdint.h>
# include <pthread.h>
# include "event.h"
# include "philo.h"

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
	enum e_simu				_state;
	pthread_mutex_t			_lock_state;
	t_simu					(*get_state)(struct s_prog *);
	void					(*set_state)(struct s_prog *, t_simu);
}	t_prog;

typedef struct s_monitoring
{
	struct s_prog		prog;
	uint64_t			start_time;
	pthread_t			*threads;
	struct s_philo		*philos;
	struct s_snap_philo	*snap_philos;
	pthread_mutex_t		*forks;
	int					(*start)(struct s_monitoring *);
	void				(*maj_snap)(struct s_monitoring *);
	bool				(*one_dead)(struct s_monitoring *);
	void				(*stop)(struct s_monitoring *);

}	t_monitoring;

int		_init_monitor_memory(struct s_monitoring *this);
int		_init_monitor_mutex(struct s_monitoring *this);
int		_init_prog(struct s_prog *this, struct s_settings param);
void	_destroy_monitor_memory(struct s_monitoring *this);
void	_destroy_monitor_mutex(struct s_monitoring *this);
void	_destroy_prog(struct s_prog *this);
int		_start_monitor(struct s_monitoring *this);
bool	_one_dead_monitor(struct s_monitoring *this);
void	_maj_snap(struct s_monitoring *this);

int		init_monitor(struct s_monitoring *this, t_settings param);
void	destroy_monitor(struct s_monitoring *this);
void	give_permission_eat(struct s_monitoring *this);

int		get_param(struct s_settings *param, int argc, char **argv);

#endif
