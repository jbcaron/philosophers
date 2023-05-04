/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:05:24 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/04 14:57:47 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"
#include "simulation.h"
#include "error.h"

/*
static void	(*g_check_state_philo[5])(t_philo*, t_prog*) = {
	check_idle,
	check_eat,
	check_sleep,
	check_thinking,
	check_dead
};
function in routine:
	g_check_state_philo[philo->get_state(philo)](philo, prog);
*/

void	*thread_philo(void *data_thread)
{
	t_philo	*data;

	data = (t_philo *)data_thread;
	routine_philo(data, data->prog);
	return (EXIT_SUCCESS);
}

void	routine_philo(t_philo *philo, t_prog *prog)
{
	t_state	state;

	while (prog->get_state(prog) != STOP)
	{
		state = philo->get_state(philo);
		if (state == IDLE)
			check_idle(philo, prog);
		if (state == EAT)
			check_eat(philo, prog);
		if (state == SLEEP)
			check_sleep(philo, prog);
		if (state == THINKING)
			check_thinking(philo, prog);
		if (state == DEAD)
			check_dead(philo, prog);
	}
	philo->stop(philo);
}
