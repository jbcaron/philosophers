/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_methods_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:10:22 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/04 16:14:58 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"
#include "philo.h"
#include "simulation.h"

t_snap_philo	_get_snap_philo(t_philo *this)
{
	t_snap_philo	snap;

	pthread_mutex_lock(&this->_lock_data);
	snap.time_last_meal = this->_last_meal_time;
	snap.nb_meal = this->_nb_meal;
	snap.state = this->_state;
	snap.eat_permission = this->_eat_permission;
	pthread_mutex_unlock(&this->_lock_data);
	return (snap);
}

void	_allow_eat_philo(t_philo *this)
{
	pthread_mutex_lock(&this->_lock_data);
	this->_eat_permission = true;
	pthread_mutex_unlock(&this->_lock_data);
}

bool	_can_eat_philo(t_philo *this)
{
	bool	allow_eat;

	pthread_mutex_lock(&this->_lock_data);
	allow_eat = this->_eat_permission;
	pthread_mutex_unlock(&this->_lock_data);
	return (allow_eat);
}

void	_pickup_forks_philo(t_philo *this, t_prog *prog)
{
	t_event	event;

	event.philo_id = this->id;
	event.type = TAKE_FORK;
	pthread_mutex_lock(this->_left_fork);
	event.timestamp = get_time_ms();
	prog->event_buf.push(&prog->event_buf, &event);
	pthread_mutex_lock(this->_right_fork);
	event.timestamp = get_time_ms();
	prog->event_buf.push(&prog->event_buf, &event);
}

void	_drop_forks_philo(t_philo *this)
{
	pthread_mutex_unlock(this->_left_fork);
	pthread_mutex_unlock(this->_right_fork);
	this->_eat_permission = false;
}
