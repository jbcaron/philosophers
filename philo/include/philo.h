/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:06:03 by jcaron            #+#    #+#             */
/*   Updated: 2023/04/13 12:57:36 by jcaron           ###   ########.fr       */
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
	DEAD,
	ERROR
}	t_state;

typedef struct s_snap_philo
{
	uint64_t		last_time;
	int32_t			nb_meal;
	t_state			state;
}	t_snap_philo;

typedef struct s_philo
{
	uint32_t		id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int32_t			nb_meal;
	uint64_t		last_meal_time;
	bool			eat_permission;
	t_state			state;
	pthread_mutex_t	lock_data;
	t_state			(*get_state)(struct s_philo *);
	t_state			(*set_state)(struct s_philo *, t_state);
	t_snap_philo	(*get_snap)(struct s_philo *);
	void			(*allow_eat)(struct s_philo *);
	bool			(*can_eat)(struct s_philo *);
	void			(*new_meal)(struct s_philo *, uint64_t);
}	t_philo;

#endif
