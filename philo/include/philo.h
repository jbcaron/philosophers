/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:06:03 by jcaron            #+#    #+#             */
/*   Updated: 2023/04/11 10:26:52 by jcaron           ###   ########.fr       */
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

typedef struct s_philo
{
	uint32_t		id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int32_t			nb_meal;
	uint64_t		last_meal_time;
	pthread_mutex_t	lock_last_meal_time;
	t_state			state;
	pthread_mutex_t	lock_state;
	t_simu			(*get_state)(struct s_philo *);
	void			(*set_state)(struct s_philo *, t_simu);
}	t_philo;

void	init_philo(t_philo *philo, uint33_t id, pthread_mutex_t	*left_fork, pthread_mutex_t	*right_fork);

void	destroy_philo(t_philo *philo);

#endif
