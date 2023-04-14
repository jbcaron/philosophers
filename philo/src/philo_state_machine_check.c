/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state_machine_check.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:20:24 by jcaron            #+#    #+#             */
/*   Updated: 2023/04/14 15:47:33 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "simulation.h"
#include "error.h"

void	check_idle(t_philo *philo, t_prog *prog)
{
	if (prog->get_state(prog) == START)
	{
		philo->set_state(philo, THINK);
		philo->new_meal(philo, get_time_ms());
		upon_enter_think(philo, prog);
	}
}

void	check_eat(t_philo *philo, t_prog *prog)
{
	uint64_t	last_meal;

	last_meal = philo->get_last_meal(philo);
	if (last_meal >= prog->param.time_to_die)
	{
		philo->set_state(philo, DEAD);
		upon_enter_dead(philo, prog);
	}
	else if (last_meal >= prog->param.time_to_eat)
	{
		philo->set_state(philo, SLEEP);
		upon_enter_sleep(philo, prog);
	}
}

void	check_sleep(t_philo *philo, t_prog *prog)
{
	uint64_t	last_meal;

	last_meal = philo->get_last_meal(philo);
	if (last_meal >= prog->param.time_to_die)
	{
		philo->set_state(philo, DEAD);
		upon_enter_dead(philo, prog);
	}
	else if (last_meal >= (prog->param.time_to_eat + prog->param.time_to_eat))
	{
		philo->set_state(philo, THINK);
		upon_enter_think(philo, prog);
	}
}

void	check_thinking(t_philo *philo, t_prog *prog)
{
	uint64_t	last_meal;

	last_meal = philo->get_last_meal(philo);
	if (last_meal >= prog->param.time_to_die)
	{
		philo->set_state(philo, DEAD);
		upon_enter_dead(philo, prog);
	}
	else if (philo->can_eat(philo))
	{
		philo->pickup_forks(philo, prog);
	}
}

void	check_dead(t_philo *philo, t_prog *prog)
{
}
