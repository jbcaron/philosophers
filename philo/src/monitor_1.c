/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:09:18 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/03 19:29:47 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "utils.h"
#include "simulation.h"
#include "event.h"
#include "philo.h"

int	_init_monitor_memory(t_monitoring *this)
{
	int32_t	nb_philo;

	nb_philo = this->prog.param.nb_philo;
	this->threads = malloc(sizeof(*this->threads) * nb_philo);
	this->philos = malloc(sizeof(*this->philos) * nb_philo);
	this->snap_philos = malloc(sizeof(*this->snap_philos) * nb_philo);
	this->forks = malloc(sizeof(*this->forks) * nb_philo);
	if (!this->threads || !this->philos || !this->snap_philos || !this->forks)
	{
		_destroy_monitor_memory(this);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	_init_monitor_philo(t_monitoring *this)
{
	int32_t	i;
	int32_t	nb_philo;

	nb_philo = this->prog.param.nb_philo;
	i = -1;
	while (++i < nb_philo)
	{
		if (init_philo(&this->philos[i], i, this))
		{
			while (--i >= 0)
				destroy_philo(&this->philos[i]);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	_init_monitor_mutex(t_monitoring *this)
{
	int32_t	i;
	int32_t	nb_philo;

	nb_philo = this->prog.param.nb_philo;
	i = -1;
	while (++i < nb_philo)
	{
		if (pthread_mutex_init(&this->forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&this->forks[i]);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	_init_prog(t_prog *this, t_settings param)
{
	this->param = param;
	if (init_event_buffer(&this->event_buf, param.nb_philo * 4))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&this->_lock_state, NULL))
	{
		destroy_event_buffer(&this->event_buf);
		return (EXIT_FAILURE);
	}
	this->_state = WAIT;
	this->get_state = _get_state_simu;
	this->set_state = _set_state_simu;
	return (EXIT_SUCCESS);
}

void	_destroy_prog(t_prog *this)
{
	this->_state = STOP;
	destroy_event_buffer(&this->event_buf);
	pthread_mutex_destroy(&this->_lock_state);
}
