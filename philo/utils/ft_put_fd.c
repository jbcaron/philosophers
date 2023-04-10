/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:12:16 by jcaron            #+#    #+#             */
/*   Updated: 2023/01/10 11:08:19 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_put_fd.h"
#include "ft_str.h"

int	ft_putchar_fd(char c, int fd)
{
	return ((int)write(fd, &c, 1));
}

int	ft_putendl_fd(char *str, int fd)
{
	int	nb_write;

	nb_write = 0;
	if (str)
		nb_write += (int)write(fd, str, ft_strlen(str));
	if (nb_write >= 0)
		nb_write += (int)write(fd, "\n", 1);
	return (nb_write);
}

int	ft_putstr_fd(char *str, int fd)
{
	if (str)
		return ((int)write(fd, str, ft_strlen(str)));
	return (0);
}
