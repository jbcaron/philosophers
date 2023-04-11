/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:05:24 by jcaron            #+#    #+#             */
/*   Updated: 2023/04/11 19:27:35 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "simulation.h"
#include "error.h"

/**
void	pickup_fork(pthread_mutex_t	*fork)
{
	pthread_mutex_lock(fork);
}
**/

t_state	get_state_philo(t_philo *this)
{
	t_state	state;

	pthread_mutex_lock(&this->lock_data);
	state = this->state;
	pthread_mutex_unlock(&this->lock_data);
	return (state);
}

t_state	set_state_philo(t_philo *this, t_state state)
{
	pthread_mutex_lock(&this->lock_data);
	this->state = state;
	pthread_mutex_unlock(&this->lock_data);
	return (state);
}

t_snap_philo	get_snap_philo(t_philo *this)
{
	t_snap_philo	snap;

	pthread_mutex_lock(&this->lock_data);
	snap.last_time = this->last_meal_time;
	snap.nb_meal = this->nb_meal;
	snap.state = this->state;
	pthread_mutex_unlock(&this->lock_data);
	return (snap);
}

bool	can_eat_philo(t_philo *this)
{
	bool	can_eat;

	pthread_mutex_lock(&this->lock_data);
	can_eat = this->eat_permission;
	pthread_mutex_unlock(&this->lock_data);
	return (can_eat);
}

void	allow_eat_philo(t_philo *this)
{
	pthread_mutex_lock(&this->lock_data);
	this->eat_permission = true;
	pthread_mutex_unlock(&this->lock_data);
}

void	new_meal_philo(t_philo *this)
{
	uint64_t	time;

	time = get_time_ms();
	pthread_mutex_lock(&this->lock_data);
	this->last_meal_time = time;
	++this->nb_meal;
	this->can_eat = false;
	pthread_mutex_unlock(&this->lock_data);
}

int	init_philo(t_philo *this, uint32_t id, pthread_mutex_t	*left_fork, pthread_mutex_t	*right_fork)
{
	this->id = id;
	this->left_fork = left_fork;
	this->right_fork = right_fork;
	this->meal.nb = -1;
	this->state = IDLE;
	this->get_state = get_state_philo;
	this->set_state = set_state_philo;
	this->get_snap = get_snap_philo;
	this->allow_eat = allow_eat_philo;
	this->can_eat = can_eat_philo;
	this->new_meal = new_meal_philo;
	if (pthread_mutex_init(&this->lock_data, NULL))
		return (ERROR_MUTEX);
	return (SUCCESS);
}

void	destroy_philo(t_philo *this)
{
	this->id = 0;
	pthread_mutex_destroy(&this->lock_data);
}

void	upon_enter_idle(t_philo *philo, t_prog *prog)
{
}

void	upon_enter_eat(t_philo *philo, t_prog *prog)
{
}

void	upon_enter_sleep(t_philo *philo, t_prog *prog)
{
}

void	upon_enter_think(t_philo *philo, t_prog *prog)
{
}

void	upon_enter_dead(t_philo *philo, t_prog *prog)
{
}

static void	(*g_upon_state_philo[5])(t_philo*, t_prog*) = {
	upon_enter_idle,
	upon_enter_eat,
	upon_enter_sleep,
	upon_enter_think,
	upon_enter_dead
};

void	check_idle(t_philo *philo, t_prog *prog)
{

	if (prog->state == START)
	{
		philo->state = THINK;
		philo->last_meal_time = prog->start_time;
		upon_enter_think(prog, philo);
	}
}

void	check_eat(t_philo *philo, t_prog *prog)
{
	uint64_t	last_meal;

	last_meal = philo->get_last_meal(philo);
	if (last_meal >= prog->param.time_to_eat)
	{
		philo->set_state(philo, SLEEP);
		upon_enter_sleep(philo, prog);
	}
	if (philo->last_meal_time >= prog->param.time_to_die)
	{
		philo->set_state(philo, DEAD);
		upon_enter_dead(philo, prog);
	}
}

void	check_sleep(t_philo *philo, t_prog *prog)
{
	uint64_t	last_meal;

	last_meal = philo->get_last_meal(philo);
	if (last_meal >= (prog->param.time_to_eat + prog->param.time_to_eat))
	{
		philo->set_state(philo, THINK);
		upon_enter_think(philo, prog);
	}
	if (philo->last_meal_time >= prog->param.time_to_die)
	{
		philo->set_state(philo, DEAD);
		upon_enter_dead(philo, prog);
	}
}

void	check_thinking(t_philo *philo, t_prog *prog)
{
}

void	check_dead(t_philo *philo, t_prog *prog)
{
}
static void	(*g_check_state_philo[5])(t_prog*, t_philo*) = {
	check_idle,
	check_eat,
	check_sleep,
	check_thinking,
	check_dead
};

void	philo(t_philo *philo, t_prog *prog)
{
	while (prog->get_state(prog) != STOP) 
	{
		g_check_state_philo[philo->get_state(philo)](prog, philo);
	}
	destroy_philo(philo);
	pthread_exit(0);
}
