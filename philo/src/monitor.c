/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:09:18 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/01 15:12:34 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "simulation.h"
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
			while (--i)
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
			while (--i)
				pthread_mutex_destroy(&this->forks[i]);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_FAILURE);
}

int	_init_prog(t_prog *this, t_settings param)
{
	this->param = param;
	this->_state = WAIT;
	if (init_event_buffer(&this->event_buf, param.nb_philo * 2))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&this->_lock_state, NULL))
	{
		destroy_event_buffer(&this->event_buf);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	_destroy_prog(t_prog *this)
{
	this->_state = STOP;
	destroy_event_buffer(&this->event_buf);
	pthread_mutex_destroy(&this->_lock_state);
}

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

int	init_monitor(t_monitoring *this, t_settings param)
{
	if (init_monitor_memory(this))
		return (EXIT_FAILURE);
	if (init_monitor_mutex(this))
	{
		_destroy_monitor_memory(this);
		return (EXIT_FAILURE);
	}
	if (init_prog(&this->prog, param))
	{
		_destroy_monitor_mutex(this);
		_destroy_monitor_memory(this);
		return (EXIT_FAILURE);
	}
	this->start = _start_monitor;
	this->maj_snap = _maj_snap;
	return (EXIT_SUCCESS);
}

void	destroy_monitor(t_monitoring *this)
{
	_destroy_monitor_mutex(this);
	_destroy_monitor_memory(this);
	_destroy_prog(&this->prog);
}

int	_start_monitor(t_monitoring *this)
{
	int32_t			i;
	int32_t			nb_philo;

	nb_philo = this->prog.param.nb_philo;
	i = -1;
	while (++i < nb_philo)
	{
		if (pthread_create(&this->threads[i], NULL, thread_philo, (void *)(&this->philos[i])))
		{
			this->prog.set_state(&this->prog, STOP);
			while (--i)
				pthread_join(this->threads[i], NULL);
			return (EXIT_FAILURE);
		}
	}
	this->start_time = get_time_ms();
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
	int		i;

	nb_philo = this->prog.param.nb_philo;
	i = -1;
	while (++i < nb_philo)
	{
		if (this->snap_philos[i].state == DEAD)
			return (false);
	}
	return (true);
}

void	_maj_snap(t_monitoring *this)
{
	int32_t	nb_philo;
	int		i;

	nb_philo = this->prog.param.nb_philo;
	i = -1;
	while (++i < nb_philo)
		this->snap_philos[i] = this->philos[i].get_snap(&this->philos[i]);
}

/**
 * @brief Gives permission to philosophers to eat based on their state and
 * neighbors.
 * 
 * This function iterates through all philosophers and checks if they are
 * allowed to eat based on their current state, their neighbors' states, and
 * their last meal times. If a philosopher is allowed to eat, their
 * eat_permission is set to true and the allow_eat() function is called for
 * that philosopher.
 *
 * @param this Pointer to a t_monitoring structure containing the philosophers
 * and their states.
 */

void	give_permission_eat(t_monitoring *this)
{
	int32_t	nb_philo;
	int32_t	left_id;
	int32_t	right_id;
	int32_t	i;

	nb_philo = this->prog.param.nb_philo;
	i = -1;
	while (++i < nb_philo)
	{
		if (i == 0)
			left_id = nb_philo - 1;
		else
			left_id = i - 1;
		right_id = (i + 1) % (nb_philo);
		if (this->snap_philos[i].eat_permission == false &&
			this->snap_philos[i].state == THINKING &&
			this->snap_philos[left_id].eat_permission == false &&
			this->snap_philos[right_id].eat_permission == false &&
			this->snap_philos[i].time_last_meal >= this->snap_philos[left_id].time_last_meal &&
			this->snap_philos[i].time_last_meal >= this->snap_philos[right_id].time_last_meal)
		{
			this->snap_philos[i].eat_permission = true;
			this->philos[i].allow_eat(&this->philos[i]);
		}
	}
}
