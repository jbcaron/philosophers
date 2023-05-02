/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state_machine_actions.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:20:37 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/02 12:56:53 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "simulation.h"
#include "utils.h"

void	upon_exit_idle(t_philo *philo, t_prog *prog)
{
	(void)prog;
	philo->new_meal(philo, get_time_ms());
}

void	upon_enter_eat(t_philo *philo, t_prog *prog)
{
	t_event	event;

	event.timestamp = get_time_ms();
	event.philo_id = philo->id;
	event.type = EATING;
	philo->new_meal(philo, event.timestamp);
	prog->event_buf.push(&prog->event_buf, &event);
}

void	upon_enter_sleep(t_philo *philo, t_prog *prog)
{
	t_event	event;

	event.timestamp = get_time_ms();
	event.philo_id = philo->id;
	event.type = SLEEPING;
	prog->event_buf.push(&prog->event_buf, &event);
}

void	upon_enter_think(t_philo *philo, t_prog *prog)
{
	t_event	event;

	event.timestamp = get_time_ms();
	event.philo_id = philo->id;
	event.type = THINKING;
	prog->event_buf.push(&prog->event_buf, &event);
}

void	upon_enter_dead(t_philo *philo, t_prog *prog)
{
	t_event	event;

	event.timestamp = get_time_ms();
	event.philo_id = philo->id;
	event.type = DIED;
	prog->event_buf.push(&prog->event_buf, &event);
}
