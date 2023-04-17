/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_methods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:10:22 by jcaron            #+#    #+#             */
/*   Updated: 2023/04/17 18:00:07 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"
#include "simulation.h"
#include "error.h"

int	init_philo(t_philo *this, uint32_t id, pthread_mutex_t	*left_fork, pthread_mutex_t	*right_fork)
{
	this->id = id;
	this->_left_fork = left_fork;
	this->_right_fork = right_fork;
	this->_nb_meal = -1;
	this->_state = IDLE;
	this->get_state = _get_state_philo;
	this->set_state = _set_state_philo;
	this->get_last_meal = _get_last_meal_philo;
	this->get_snap = _get_snap_philo;
	this->allow_eat = _allow_eat_philo;
	this->can_eat = _can_eat_philo;
	this->pickup_forks = _pickup_forks_philo;
	this->new_meal = _new_meal_philo;
	this->stop = _stop_philo;
	if (pthread_mutex_init(&this->_lock_data, NULL))
		return (ERROR_MUTEX);
	return (SUCCESS);
}

void	destroy_philo(t_philo *this)
{
	this->id = 0;
	pthread_mutex_destroy(&this->_lock_data);
}

t_state	_get_state_philo(t_philo *this)
{
	t_state	state;

	pthread_mutex_lock(&this->_lock_data);
	state = this->_state;
	pthread_mutex_unlock(&this->_lock_data);
	return (state);
}

t_state	_set_state_philo(t_philo *this, t_state state)
{
	pthread_mutex_lock(&this->_lock_data);
	this->_state = state;
	pthread_mutex_unlock(&this->_lock_data);
	return (state);
}

uint64_t	_get_last_meal_philo(t_philo *this)
{
	uint64_t	time;

	pthread_mutex_lock(&this->_lock_data);
	time = this->_last_meal_time;
	pthread_mutex_unlock(&this->_lock_data);
	return (time);
}

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
	bool	can_eat;

	pthread_mutex_lock(&this->_lock_data);
	can_eat = this->_eat_permission;
	pthread_mutex_unlock(&this->_lock_data);
	return (can_eat);
}

void	_pickup_forks_philo(t_philo *this, t_prog *prog)
{
	t_event	event;

	event.philo_id = this->id;
	event.type = TAKE_FORK;
	pthread_mutex_lock(this->_left_fork);
	event.timestamp = get_time_ms();
	prog->event_buf.push(&prog->event_buf, &event);
	pthread_mutex_lock(this->_left_fork);
	event.timestamp = get_time_ms();
	prog->event_buf.push(&prog->event_buf, &event);
}

void	_new_meal_philo(t_philo *this, uint64_t time)
{
	pthread_mutex_lock(&this->_lock_data);
	this->_last_meal_time = time;
	++this->_nb_meal;
	this->can_eat = false;
	pthread_mutex_unlock(&this->_lock_data);
}

void	_stop_philo(t_philo *this)
{
	if (this->get_state(this) == EAT)
	{
		pthread_mutex_unlock(this->_left_fork);
		pthread_mutex_unlock(this->_right_fork);
	}
	destroy_philo(this);
	pthread_exit(EXIT_SUCCESS);
}
