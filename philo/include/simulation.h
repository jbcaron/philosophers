/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:11:52 by jcaron            #+#    #+#             */
/*   Updated: 2023/04/11 10:42:02 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
#define SIMULATION_H

typedef enum e_simu
{
	WAIT,
	START,
	STOP
}	t_simu;

typedef enum e_parity
{
	ODD,
	PEER
}	t_parity;

typedef struct s_settings
{
	int32_t			nb_philo;
	int32_t			time_to_die;
	int32_t			time_to_eat;
	int32_t			time_to_sleep;
	int32_t			nb_meal;
}	t_settings;

typedef struct s_prog
{
	t_settings		param;
	uint64_t		start_time;
	t_simu			state;
	pthread_mutex_t	lock_state;
	pthread_mutex_t	*forks;
	t_event_buffer	event_buf;
	t_simu			(*get_state)(struct s_prog *);
	void			(*set_state)(struct s_prog *, t_simu);
}	t_prog;

void	init_prog(t_prog *this, t_param param);

#endif
