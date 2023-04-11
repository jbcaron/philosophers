/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:10:03 by jcaron            #+#    #+#             */
/*   Updated: 2023/04/11 11:52:34 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "simulation.h"

t_simu	get_state_simu(t_prog *this)
{
	t_simu	state;

	pthread_mutex_lock(&this->lock_state);
	state = this->state;
	pthread_mutex_unlock(&this->lock_state);
	return (state);
}

void	set_state_simu(t_prog *this, t_simu state)
{
	pthread_mutex_lock(&this->lock_state);
	this->state = state;
	pthread_mutex_unlock(&this->lock_state);
}

int	init_prog(t_prog *this, t_param param, t_event_buffer event_buf)
{
	uint32_t	i;

	this->param = param;
	start_time = 0;
	this->state = WAIT;
	this->forks = malloc(sizeof(*this->forks) * nb_forks);
	if (! this->forks)
		return (ERROR_MALLOC)
	this->event_buf = event_buf;
	this->get_state = get_state_simu;
	this->set_state = set_state_simu;
	if (pthread_mutex_init(&this->lock_state, NULL))
	{
		free(this->forks);
		return (ERROR_MUTEX);
	}
	i = (uint32_t)(-1);
	while (++i < param.nb_philo)
	{
		if (pthread_mutex_init(&this->forks[i], NULL))
		{
			while (--i)
				pthread_mutex_destroy(&this->forks[i]);
			pthread_mutex_destroy(&this->lock_state);
			free(this->forks);
			return (ERROR_MUTEX);
		}
	}
	return (SUCCESS);
}

void	destroy_prog(t_prog *this)
{
	uint32_t	i;

	start_time = 0;
	this->state = END;
	this->get_state = NULL;
	this->set_state = NULL;
	pthread_mutex_destroy(&this->lock_state);
	i = (uint32_t)(-1);
	while (++i < this->param.nb_philo)
		pthread_mutex_destroy(this->forks[i]);
	this->forks = NULL;
}
