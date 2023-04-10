/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:34:45 by jcaron            #+#    #+#             */
/*   Updated: 2023/02/06 14:50:53 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "get_next_line.h"
#include "ft_str.h"
#include "ft_malloc.h"

static size_t	strlenn(t_buffer *buf)
{
	char	*str;
	size_t	i;
	size_t	ofset;

	ofset = buf->id;
	str = buf->buf;
	i = 0;
	while (i + ofset < buf->len)
	{
		if (str[i + ofset] == '\n')
		{
			i ++;
			break ;
		}
	i++;
	}
	return (i);
}

static void	strcatalloc(t_line *line, t_buffer *buf)
{
	char	*new;
	size_t	add_len;

	add_len = strlenn(buf);
	new = ft_malloc(sizeof(char) * (line->len + add_len + 1));
	if (line->len > 0)
		ft_strcpy(new, line->str);
	else
		new[0] = '\0';
	ft_strncat(new, &buf->buf[buf->id], add_len);
	ft_free(line->str);
	line->str = new;
	line->len += add_len;
	buf->id += add_len;
	if (line->str[line->len - 1] == '\n')
		line->str[--line->len] = '\0';
}

static ssize_t	ft_read(t_buffer *buf, int fd)
{
	ssize_t	ret_read;

	ret_read = read(fd, buf->buf, BUFFER_SIZE);
	if (ret_read < 0)
		return (ret_read);
	buf->len = (size_t)ret_read;
	buf->id = 0;
	return (ret_read);
}

char	*get_next_line(int fd)
{
	static t_buffer	buf;
	t_line			line;

	line.str = NULL;
	line.len = 0;
	while (1)
	{
		if (buf.id == buf.len || buf.len == 0)
		{
			if (ft_read(&buf, fd) < 0)
				return (ft_free(line.str), NULL);
			if (buf.len == 0)
				return (line.str);
		}
		strcatalloc(&line, &buf);
		if (buf.buf[buf.id - 1] == '\n')
			return (line.str);
	}
}
