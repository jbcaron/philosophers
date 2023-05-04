/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:09:18 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/04 16:23:58 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "utils.h"
#include "simulation.h"
#include "event.h"
#include "philo.h"

void	_set_state_simu(t_prog *this, t_simu state)
{
	pthread_mutex_lock(&this->_lock_state);
	this->_state = state;
	pthread_mutex_unlock(&this->_lock_state);
}

t_simu	_get_state_simu(t_prog *this)
{
	t_simu	state;

	pthread_mutex_lock(&this->_lock_state);
	state = this->_state;
	pthread_mutex_unlock(&this->_lock_state);
	return (state);
}

int	_start_monitor(t_monitoring *this)
{
	int32_t			i;
	int32_t			nb_philo;

	nb_philo = this->prog.param.nb_philo;
	i = -1;
	while (++i < nb_philo)
	{
		if (pthread_create(&this->threads[i], NULL, thread_philo, \
			(void *)(&this->philos[i])))
		{
			this->prog.set_state(&this->prog, STOP);
			while (--i >= 0)
				pthread_join(this->threads[i], NULL);
			return (EXIT_FAILURE);
		}
	}
	i = -1;
	this->prog.start_time = get_time_ms();
	while (++i < nb_philo)
		this->philos[i]._last_meal_time = this->prog.start_time;
	this->prog.set_state(&this->prog, START);
	return (EXIT_SUCCESS);
}

void	_stop_monitor(t_monitoring *this)
{
	int32_t			i;
	int32_t			nb_philo;

	nb_philo = this->prog.param.nb_philo;
	this->prog.set_state(&this->prog, STOP);
	i = -1;
	while (++i < nb_philo)
		pthread_join(this->threads[i], NULL);
}

bool	_one_dead_monitor(t_monitoring *this)
{
	int32_t	nb_philo;
	int32_t	i;

	nb_philo = this->prog.param.nb_philo;
	i = -1;
	while (++i < nb_philo)
	{
		if (this->snap_philos[i].state == DEAD)
			return (true);
	}
	return (false);
}
