/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:52:30 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/01 13:00:52 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "simulation.h"

void	*fn_thread(void *nb_thread)
{
	(*(int *)nb_thread)++;
	printf("I'm a the thread: %d\n", *(int *)nb_thread);
	pthread_exit(EXIT_SUCCESS);
}

void	monitor_routine(t_monitoring *monitor)
{
	t_prog	*prog;

	prog = &monitor->prog;
	while (prog->get_state(prog) != STOP)
	{
		prog->event_buf.flush(&prog->event_buf, monitor->start_time);
	}
}

int	main(int argc, char **argv)
{
	t_monitoring	monitor;
	t_settings		param;

	if (get_param(&param, argc, argv))
	{
		printf("Error Usage");
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
