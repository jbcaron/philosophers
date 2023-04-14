/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:52:30 by jcaron            #+#    #+#             */
/*   Updated: 2023/04/14 16:09:50 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "data.h"

void	*fn_thread(void *nb_thread)
{
	(*(int *)nb_thread)++;
	printf("I'm a the thread: %d\n", *(int *)nb_thread);
	pthread_exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	pthread_t	new_thread;
	int			nb_thread;

	nb_thread = 1;
	pthread_create(&new_thread, NULL, fn_thread, (void *)(&nb_thread));
	pthread_join(new_thread, NULL);
	return (0);
}

void	main_routine()
{
	while (prog->get_state(prog) != STOP)
	{

	}
}

bool	