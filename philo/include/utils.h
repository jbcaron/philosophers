/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:03:45 by jcaron            #+#    #+#             */
/*   Updated: 2023/05/02 13:21:41 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

size_t		ft_strlen(const char *str);
int			ft_strcmp(const char *s1, const char *s2);
bool		ft_isspace(char c);
bool		ft_isdigit(char c);
bool		ft_str_is_digit(const char *str);
int32_t		atoint32(const char *str);
uint64_t	get_time_ms(void);
uint64_t	get_time_us(void);

#endif
