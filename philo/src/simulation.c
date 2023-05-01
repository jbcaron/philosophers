/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:10:03 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/01 14:46:58 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "simulation.h"
#include "error.h"

t_simu	get_state_simu(t_prog *this)
{
	t_simu	state;

	pthread_mutex_lock(&this->_lock_state);
	state = this->_state;
	pthread_mutex_unlock(&this->_lock_state);
	return (state);
}

void	set_state_simu(t_prog *this, t_simu state)
{
	pthread_mutex_lock(&this->_lock_state);
	this->_state = state;
	pthread_mutex_unlock(&this->_lock_state);
}

void	init_prog(t_prog *this, t_settings param, t_event_buffer event_buf)
{
	this->param = param;
	this->_state = WAIT;
	this->event_buf = event_buf;
	this->get_state = get_state_simu;
	this->set_state = set_state_simu;
}

void	destroy_prog(t_prog *this)
{
	this->_state = STOP;
	this->get_state = NULL;
	this->set_state = NULL;
	pthread_mutex_destroy(&this->_lock_state);
}
