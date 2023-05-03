/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:09:18 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/03 19:30:07 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "utils.h"
#include "simulation.h"
#include "event.h"
#include "philo.h"

void	_destroy_monitor_memory(t_monitoring *this)
{
	free(this->threads);
	free(this->philos);
	free(this->snap_philos);
	free(this->forks);
}

void	_destroy_monitor_mutex(t_monitoring *this)
{
	int32_t	i;
	int32_t	nb_philo;

	nb_philo = this->prog.param.nb_philo;
	i = -1;
	while (++i < nb_philo)
		pthread_mutex_destroy(&this->forks[i]);
}

static void	init_monitor_var(t_monitoring *this)
{
	this->start = _start_monitor;
	this->maj_snap = _maj_snap;
	this->one_dead = _one_dead_monitor;
	this->all_eat = _all_eat_enought;
	this->stop = _stop_monitor;
}

int	init_monitor(t_monitoring *this, t_settings param)
{
	if (_init_prog(&this->prog, param))
		return (EXIT_FAILURE);
	if (_init_monitor_memory(this))
	{
		_destroy_prog(&this->prog);
		return (EXIT_FAILURE);
	}
	if (_init_monitor_mutex(this))
	{
		_destroy_prog(&this->prog);
		_destroy_monitor_memory(this);
		return (EXIT_FAILURE);
	}
	if (_init_monitor_philo(this))
	{
		_destroy_prog(&this->prog);
		_destroy_monitor_mutex(this);
		_destroy_monitor_memory(this);
		return (EXIT_FAILURE);
	}
	init_monitor_var(this);
	return (EXIT_SUCCESS);
}

void	destroy_monitor(t_monitoring *this)
{
	_destroy_monitor_mutex(this);
	_destroy_monitor_memory(this);
	_destroy_prog(&this->prog);
}
