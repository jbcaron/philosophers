/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_closer_pow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:19:21 by jcaron            #+#    #+#             */
/*   Updated: 2023/01/26 15:25:58 by jcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "get_closer_pow.h"

/**
 * @brief Get the closest power of two greater than or equal to a given number.
 * This function calculates the closest power of two that is greater than or
 * equal to a given number n.
 * For example, for the input n=5, the function returns 8.
 *
 * @param n Number to find the closest power of two for.
 *
 * @return Closest power of two greater than or equal to n.
*/

size_t	get_closer_pow(size_t n)
{
	size_t	pow;

	pow = 1;
	while (pow < n && (pow << 1))
		pow <<= 1;
	return (pow);
}
