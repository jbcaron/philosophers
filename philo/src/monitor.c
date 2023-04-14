/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:09:18 by jcaron            #+#    #+#             */
/*   Updated: 2023/04/14 17:00:50 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "simulation.h"
#include "error.h"

int	_init_monitor_memory(t_monitoring *this)
{
	int32_t	nb_philo;

	nb_philo = this->prog->param.nb_philo;
	this->threads = malloc(sizeof(*this->threads) * nb_philo);
	if (!this->threads)
		return (ERROR_MALLOC);
	this->philos = malloc(sizeof(*this->philos) * nb_philo);
	if (!this->philos)
	{
		free(this->threads);
		return (ERROR_MALLOC);
	}
	this->forks = malloc(sizeof(*this->forks) * nb_philo);
	if (!this->forks)
	{
		free(this->threads);
		free(this->philos);
		return (ERROR_MALLOC);
	}
	return (SUCCESS);
}

int	_init_monitor_mutex(t_monitoring *this)
{
	int32_t	i;
	int32_t	nb_philo;

	nb_philo = this->prog->param.nb_philo;
	i = -1;
	while (++i < nb_philo)
	{
		if (pthread_mutex_init(&this->forks[i], NULL))
		{
			while (--i)
				pthread_mutex_destroy(&this->forks[i]);
			return (ERROR_MUTEX);
		}
	}
	return (SUCCESS);
}

void	_destroy_monitor_memory(t_monitoring *this)
{
	free(this->threads);
	free(this->philos);
	free(this->forks);
}

void	_destroy_monitor_mutex(t_monitoring *this)
{
	int32_t	i;
	int32_t	nb_philo;

	nb_philo = this->prog->param.nb_philo;
	i = -1;
	while (++i < nb_philo)
		pthread_mutex_destroy(&this->forks[i]);
}

int	init_monitor(t_monitoring *this, uint32_t nb_philo)
{
	int	error;

	error = _init_monitor_memory(this);
	if (error)
		return (error);
	error = _init_monitor_mutex(this);
	if (error)
	{
		_destroy_monitor_memory(this);
		return (error);
	}
	return (SUCCESS);
}

void	destroy_monitor(t_monitoring *this)
{
	_destroy_monitor_mutex(this);
	_destroy_monitor_memory(this);
}

int	_start_thread_monitor(t_monitoring *this)
{
	int32_t			i;
	int32_t			nb_philo;
	t_data_thread	data;

	nb_philo = this->prog.param.nb_philo;
	data.prog = &this->prog;
	i = -1;
	while (++i < nb_philo)
	{
		if (pthread_create(&this->threads[i], NULL, thread_philo, (void *)(&data)))
		{
			this->prog.set_state(&this->prog, STOP);
			return (ERROR_THREAD);
		}
	}
	this->prog.set_state(&this->prog, START);
	return (SUCCESS);
}
