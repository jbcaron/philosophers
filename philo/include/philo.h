/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:06:03 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/03 16:47:41 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdint.h>
# include <stdbool.h>
# include <pthread.h>

struct	s_prog;
struct	s_monitoring;

typedef enum e_state
{
	IDLE,
	EAT,
	SLEEP,
	THINK,
	DEAD,
	//ERROR
}	t_state;

typedef struct s_snap_philo
{
	uint64_t		time_last_meal;
	int32_t			nb_meal;
	enum e_state	state;
	bool			eat_permission;
}	t_snap_philo;

typedef struct s_philo
{
	struct s_prog	*prog;
	uint64_t		_last_meal_time;
	uint32_t		id;
	int32_t			_nb_meal;
	pthread_mutex_t	*_left_fork;
	pthread_mutex_t	*_right_fork;
	pthread_mutex_t	_lock_data;
	enum e_state	_state;
	bool			_eat_permission;
	t_state			(*get_state)(struct s_philo *);
	t_state			(*set_state)(struct s_philo *, t_state);
	uint64_t		(*get_last_meal)(struct s_philo *);
	t_snap_philo	(*get_snap)(struct s_philo *);
	void			(*allow_eat)(struct s_philo *);
	bool			(*can_eat)(struct s_philo *);
	void			(*pickup_forks)(struct s_philo *, struct s_prog *);
	void			(*drop_forks)(struct s_philo *);
	void			(*new_meal)(struct s_philo *, uint64_t);
	void			(*stop)(struct s_philo *);
}	t_philo;

int					init_philo(struct s_philo *this, uint32_t id, struct s_monitoring *data);
void				destroy_philo(struct s_philo *this);
enum e_state		_get_state_philo(struct s_philo *this);
enum e_state		_set_state_philo(struct s_philo *this, enum e_state state);
uint64_t			_get_last_meal_philo(struct s_philo *this);
struct s_snap_philo	_get_snap_philo(struct s_philo *this);
void				_allow_eat_philo(struct s_philo *this);
bool				_can_eat_philo(t_philo *this);
void				_pickup_forks_philo(struct s_philo *this, struct s_prog *prog);
void				_drop_forks_philo(t_philo *this);
void				_new_meal_philo(struct s_philo *this, uint64_t time);
void				_stop_philo(struct s_philo *this);

void				*thread_philo(void *data_thread);
void				routine_philo(struct s_philo *philo, struct s_prog *prog);

void				check_idle(struct s_philo *philo, struct s_prog *prog);
void				check_eat(struct s_philo *philo, struct s_prog *prog);
void				check_sleep(struct s_philo *philo, struct s_prog *prog);
void				check_thinking(struct s_philo *philo, struct s_prog *prog);
void				check_dead(struct s_philo *philo, struct s_prog *prog);

void				upon_exit_idle(struct s_philo *philo, struct s_prog *prog);
void				upon_enter_eat(struct s_philo *philo, struct s_prog *prog);
void				upon_enter_sleep(struct s_philo *philo, struct s_prog *prog);
void				upon_enter_think(struct s_philo *philo, struct s_prog *prog);
void				upon_enter_dead(struct s_philo *philo, struct s_prog *prog);


#endif
