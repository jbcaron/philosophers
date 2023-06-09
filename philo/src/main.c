/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:52:30 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/04 14:10:09 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "simulation.h"

static void	monitor_routine(t_monitoring *monitor)
{
	t_prog	*prog;

	prog = &monitor->prog;
	monitor->maj_snap(monitor);
	give_permission_eat(monitor);
	if (monitor->one_dead(monitor) || monitor->all_eat(monitor))
	{
		monitor->prog.set_state(&monitor->prog, STOP);
	}
	prog->event_buf.flush(&prog->event_buf, monitor->prog.start_time);
}

int	main(int argc, char **argv)
{
	t_monitoring	monitor;
	t_settings		param;

	if (get_param(&param, argc, argv))
	{
		printf("Error Usage\n");
		return (EXIT_FAILURE);
	}
	if (init_monitor(&monitor, param))
		return (EXIT_FAILURE);
	if (monitor.start(&monitor))
	{
		destroy_monitor(&monitor);
		return (EXIT_FAILURE);
	}
	while (monitor.prog.get_state(&monitor.prog) != STOP)
		monitor_routine(&monitor);
	monitor.stop(&monitor);
	destroy_monitor(&monitor);
	return (EXIT_SUCCESS);
}
