/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:24:03 by jcaron            #+#    #+#             */
/*   Updated: 2023/03/06 17:09:42 by jcaron           ###   ########.fr       */
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
