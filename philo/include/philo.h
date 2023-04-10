/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:06:03 by jcaron            #+#    #+#             */
/*   Updated: 2023/04/10 18:45:08 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdint.h>
# include <stdbool.h>
# include <pthread.h>

typedef enum e_state
{
	IDLE,
	EAT,
	SLEEP,
	THINK,
	DEAD
}	t_state;

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

typedef struct s_philo
{
	uint32_t		id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_parity		parity;
	int32_t			nb_meal;
	uint64_t		last_meal_time;
	pthread_mutex_t	lock_last_meal_time;
	pthread_mutex_t	lock_simu;
	t_state			state;
	pthread_mutex_t	lock_state;
	t_simu			(*get_state)(struct s_philo *);
	void			(*set_state)(struct s_philo *, t_simu);
}	t_philo;

#endif
