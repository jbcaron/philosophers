/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state_machine_check.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:20:24 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/03 16:29:28 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "simulation.h"
#include "utils.h"

void	check_idle(t_philo *philo, t_prog *prog)
{
	if (prog->get_state(prog) == START)
	{
		philo->set_state(philo, THINK);
		philo->new_meal(philo, get_time_ms());
		upon_exit_idle(philo, prog);
		upon_enter_think(philo, prog);
	}
}

void	check_eat(t_philo *philo, t_prog *prog)
{
	int32_t	time_since_meal;

	time_since_meal = (int32_t)(get_time_ms() - philo->get_last_meal(philo));
	if (time_since_meal >= prog->param.time_to_die)
	{
		philo->set_state(philo, DEAD);
		upon_enter_dead(philo, prog);
	}
	else if (time_since_meal >= prog->param.time_to_eat)
	{
		philo->set_state(philo, SLEEP);
		upon_enter_sleep(philo, prog);
	}
}

void	check_sleep(t_philo *philo, t_prog *prog)
{
	int32_t	time_since_meal;

	time_since_meal = (int32_t)(get_time_ms() - philo->get_last_meal(philo));
	if (time_since_meal >= prog->param.time_to_die)
	{
		philo->set_state(philo, DEAD);
		upon_enter_dead(philo, prog);
	}
	else if (time_since_meal >= (prog->param.time_to_eat + prog->param.time_to_eat))
	{
		philo->set_state(philo, THINK);
		upon_enter_think(philo, prog);
	}
}

void	check_thinking(t_philo *philo, t_prog *prog)
{
	int32_t	time_since_meal;

	time_since_meal = (int32_t)(get_time_ms() - philo->get_last_meal(philo));
	if (time_since_meal >= prog->param.time_to_die)
	{
		philo->set_state(philo, DEAD);
		upon_enter_dead(philo, prog);
	}
	else if (philo->can_eat(philo))
	{
		philo->pickup_forks(philo, prog);
		philo->set_state(philo, EAT);
		upon_enter_eat(philo, prog);
	}
}

void	check_dead(t_philo *philo, t_prog *prog)
{
	(void)philo;
	(void)prog;
}
