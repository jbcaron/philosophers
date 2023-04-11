/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <jcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 14:18:57 by jcaron            #+#    #+#             */
/*   Updated: 2023/04/11 18:21:32 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define SUCCESS					0
# define ERROR_INVALID_PARAMETER	-1
# define ERROR_MALLOC				-10
# define ERROR_PTHREAD				-20
# define ERROR_MUTEX				-21

typedef enum	e_error
{
	SUCCESS = 0,
	INVALID_PARAMETER
}	t_error;

#endif
