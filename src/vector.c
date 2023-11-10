/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   vector.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/10 02:28:35 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/10 03:25:00 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include <math.h>


// TODO Find better way of doing type conversion instead of casting each element on its own.
t_vec2i vec2f_to_vec2i(t_vec2f vec)
{
	t_vec2i result;

	result[VEC_X] = (int32_t) vec[VEC_X];
	result[VEC_Y] = (int32_t) vec[VEC_Y];
	return result;
}

t_vec2f mat_rot(t_vec2f vec, float angle)
{
	t_vec2f result;

	result[VEC_X] = (vec[VEC_X] * cos(angle)) - (vec[VEC_Y] * sin(angle));
	result[VEC_Y] = (vec[VEC_X] * sin(angle)) + (vec[VEC_Y] * cos(angle));

	return result;
}

