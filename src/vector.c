/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   vector.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/10 02:28:35 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/10 20:58:18 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include <math.h>
#include <stdint.h>

t_vec2i	vec2f_to_vec2i(t_vec2f vec)
{
	return ((t_vec2i) {vec[VEC_X],  vec[VEC_Y]});
}

t_vec2f	vec2i_to_vec2f(t_vec2i vec)
{
	return ((t_vec2f) {vec[VEC_X],  vec[VEC_Y]});
}

// https://en.wikipedia.org/wiki/Rotation_matrix
t_vec2f	vec2f_rotate2d(float angle)
{
	return ((t_vec2f) {(cos(angle)) - (sin(angle)), (sin(angle)) + (cos(angle))});
}

t_vec2f	vec2f_normalize(t_vec2f vec)
{
	float m = sqrt(vec[VEC_X] * vec[VEC_X] + vec[VEC_Y] * vec[VEC_Y]);
	return vec / m;
}

float deg_to_rad(float deg)
{
	return deg * (PI / 180);
}
