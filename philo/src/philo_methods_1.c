/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_methods_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:10:22 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/04 16:11:03 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"
#include "philo.h"
#include "simulation.h"

int	init_philo(t_philo *this, uint32_t id, t_monitoring *data)
{
	this->prog = &data->prog;
	this->id = id;
	this->_left_fork = &data->forks[id];
	this->_right_fork = &data->forks[(id + 1) % data->prog.param.nb_philo];
	this->_nb_meal = 0;
	this->_eat_permission = false;
	this->_state = IDLE;
	this->get_state = _get_state_philo;
	this->set_state = _set_state_philo;
	this->get_last_meal = _get_last_meal_philo;
	this->get_snap = _get_snap_philo;
	this->allow_eat = _allow_eat_philo;
	this->can_eat = _can_eat_philo;
	this->pickup_forks = _pickup_forks_philo;
	this->drop_forks = _drop_forks_philo;
	this->new_meal = _new_meal_philo;
	this->stop = _stop_philo;
	if (pthread_mutex_init(&this->_lock_data, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	destroy_philo(t_philo *this)
{
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
