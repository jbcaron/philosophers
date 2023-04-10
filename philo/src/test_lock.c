/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lock.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:58:26 by jcaron            #+#    #+#             */
/*   Updated: 2023/04/03 11:08:18 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void	*start_thread(void *data)
{
	pthread_mutex_t	*lock = (pthread_mutex_t *)data;

	printf("start of thread\n");
	if (pthread_mutex_lock(lock))
		perror("mutex lock");
	else
		printf("mutex is lock\n");
	sleep(2);
	pthread_mutex_unlock(lock);
	printf("mutex is unlock\n");
	printf("end of thread\n");
	return (NULL);
}

int	main(void)
{
	pthread_t		thread[5];
	pthread_mutex_t	lock;

	pthread_mutex_init(&lock, NULL);
	for (int i = 0; i < 5; i++)
	{
		if (pthread_create(&thread[i], NULL, &start_thread, (void *)&lock))
			perror("thread creation");
	}
	for (int i = 0; i < 5; i++)
		pthread_join(thread[i], NULL);
}
