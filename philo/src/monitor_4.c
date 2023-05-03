/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:09:18 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/03 19:30:41 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "utils.h"
#include "simulation.h"
#include "event.h"
#include "philo.h"

bool	_all_eat_enought(t_monitoring *this)
{
	int32_t	nb_philo;
	int32_t	i;

	if (this->prog.param.nb_meal < 0)
		return (false);
	nb_philo = this->prog.param.nb_philo;
	i = -1;
	while (++i < nb_philo)
	{
		if (this->snap_philos[i].nb_meal < this->prog.param.nb_meal)
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
	int32_t			nb_philo;
	int32_t			left_id;
	int32_t			right_id;
	int32_t			i;
	t_snap_philo	*snap;

	nb_philo = this->prog.param.nb_philo;
	if (nb_philo < 2)
		return ;
	snap = this->snap_philos;
	i = -1;
	while (++i < nb_philo)
	{
		left_id = (i + nb_philo - 1) % nb_philo;
		right_id = (i + 1) % nb_philo;
		if (!snap[i].eat_permission && snap[i].state == THINK && \
			!snap[left_id].eat_permission && !snap[right_id].eat_permission && \
			snap[left_id].state != EAT && snap[right_id].state != EAT && \
			snap[i].time_last_meal <= snap[left_id].time_last_meal && \
			snap[i].time_last_meal <= snap[right_id].time_last_meal)
		{
			snap[i].eat_permission = true;
			this->philos[i].allow_eat(&this->philos[i]);
		}
	}
}
