/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:11:44 by jcaron            #+#    #+#             */
/*   Updated: 2023/03/24 18:17:38 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>

typedef enum	e_state_action
{
	THINKING,
	EATING,
	SLEEPING
}	t_state_action;

typedef enum	e_state_life
{
	ALIVE,
	DEAD
}	t_state_life;

typedef struct s_prog
{
	uint32_t	nb_philo;
	uint32_t	time_to_die;
	uint32_t	time_to_eat;
	int32_t		max_meal;
	uint64_t	start_time;
	bool		stop;
	int8_t		*forks;
}	t_prog;

typedef struct s_philo
{
	uint32_t		id;
	uint64_t		last_meal;
	t_state_action	doing;
	t_state_life	alive;
}	t_philo;

void	start_thinking(t_philo *philo, t_prog *prog)
{

}

void	start_eating(t_philo *philo, t_prog *prog)
{
	update_last_meal(philo, prog);
}

void	start_sleeping(t_philo *philo, t_prog *prog)
{
	
}

void	state_alive(t_philo *philo, t_prog *prog)
{
	
}

void	state_dead(t_philo *philo, t_prog *prog)
{
	
}

int test1(int i)
{
	return (i);
}

int test2(int i)
{
	return (2 * i);
}

static const int	(*g_array_ptr_func[2])(int) = {
	&test1,
	&test1
};

typedef struct s_machine_philo
{

}	t_machine philo;

int	philo(t_philo *philo, t_prog *prog)
{

	g_array_ptr_func[1](4);
	while(1)
	{
		
	}
}

