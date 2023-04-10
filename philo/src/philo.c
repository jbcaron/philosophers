/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:05:24 by jcaron            #+#    #+#             */
/*   Updated: 2023/04/10 18:41:47 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/**
void	pickup_fork(pthread_mutex_t	*fork)
{
	pthread_mutex_lock(fork);
}
**/

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

t_state	get_state_philo(t_philo *this)
{
	t_state	state;

	pthread_mutex_lock(&this->lock_state);
	state = this->state;
	pthread_mutex_unlock(&this->lock_state);
	return (state);
}

void	set_state_philo(t_philo *this, t_state state)
{
	pthread_mutex_lock(&this->lock_state);
	this->state = state;
	pthread_mutex_unlock(&this->lock_state);
}

void	upon_enter_eat(t_prog *prog, t_philo *philo)
{

}

void	upon_enter_sleep(t_prog *prog, t_philo *philo)
{

}

void	upon_enter_think(t_prog *prog, t_philo *philo)
{

}

void	upon_enter_dead(t_prog *prog, t_philo *philo)
{
	
}

void	check_idle(t_prog *prog, t_philo *philo)
{
	if (prog->simulation == START)
	{
		philo->state = THINK;
		upon_enter_think(prog, philo);
	}
}

void	check_eat(t_prog *prog, t_philo *philo)
{
	if (philo->last_meal_time >= prog->param.time_to_eat)
	{
		philo->state = SLEEP;
	}
	if (philo->last_meal_time >= prog->param.time_to_die)
	{
		philo->state = DEAD;
	}
}

void	check_sleep(t_prog *prog, t_philo *philo)
{
	if (philo->last_meal_time >= (prog->param.time_to_eat + prog->param.time_to_eat))
	{
		philo->state = THINK;
	}
	if (philo->last_meal_time >= prog->param.time_to_die)
	{
		philo->state = DEAD;
	}
}

void	check_thinking(t_prog *prog, t_philo *philo)
{
	if (prog->parity == philo_parity)
	{
		pthread_mutex_lock(prog->forks[philo->id]);
		if (prog->parity == philo->parity)
		{
			pthread_mutex_lock(prog->forks[(philo->id + 1) % prog->param.nb_philo]);
			philo->last_meal_time = get_time_ms();
			philo->state = EAT;
		}
	}
}

void	check_dead(t_prog *prog, t_philo *philo)
{
}

static void	(*g_check_state_philo[5])(t_prog*, t_philo*) = {
	check_idle,
	check_eat,
	check_sleep,
	check_thinking,
	check_dead
};

void	philo(t_prog *prog, t_philo *philo)
{
	while (prog->get_state(prog) != STOP)
	{
		g_check_state_philo[philo->get_state(philo)](prog, philo);
	}
}
