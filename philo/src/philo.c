/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:05:24 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/01 14:36:35 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"
#include "simulation.h"
#include "error.h"

static void	(*g_check_state_philo[5])(t_philo*, t_prog*) = {
	check_idle,
	check_eat,
	check_sleep,
	check_thinking,
	check_dead
};

void	*thread_philo(void *data_thread)
{
	t_philo	*data;

	data = (t_philo *)data_thread;
	routine_philo(data, data->prog);
	return (EXIT_SUCCESS);
}

void	routine_philo(t_philo *philo, t_prog *prog)
{
	while (prog->get_state(prog) != STOP)
	{
		g_check_state_philo[philo->get_state(philo)](philo, prog);
	}
	philo->stop(philo);
}
