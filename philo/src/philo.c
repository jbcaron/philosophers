/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:05:24 by jcaron            #+#    #+#             */
/*   Updated: 2023/04/14 16:46:12 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_data_thread	*data;

	data = (t_data_thread *)data_thread;
	routine_philo(data->philo, data->prog);
}

void	routine_philo(t_philo *philo, t_prog *prog)
{
	while (prog->get_state(prog) != STOP)
	{
		g_check_state_philo[philo->get_state(philo)](philo, prog);
	}
	destroy_philo(philo);
	pthread_exit(EXIT_SUCCESS);
}
