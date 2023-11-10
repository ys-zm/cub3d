/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   vector.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/10 02:28:35 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/10 17:27:56 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include <math.h>
#include <stdint.h>

// TODO Maybe make these functions static inline in our header
t_vec2i	vec2f_to_vec2i(t_vec2f vec)
{
	return ((t_vec2i) {vec[VEC_X],  vec[VEC_Y]});
}

// https://en.wikipedia.org/wiki/Rotation_matrix
t_vec2f	vec2f_rotate2d(float angle)
{
	return ((t_vec2f) {(cos(angle)) - (sin(angle)), (sin(angle)) + (cos(angle))});
}
