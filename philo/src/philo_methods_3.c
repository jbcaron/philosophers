/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_methods_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:10:22 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/04 16:15:00 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"
#include "philo.h"
#include "simulation.h"

void	_new_meal_philo(t_philo *this, uint64_t time)
{
	pthread_mutex_lock(&this->_lock_data);
	this->_last_meal_time = time;
	++this->_nb_meal;
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
