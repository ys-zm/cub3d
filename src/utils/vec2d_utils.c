/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   vec2d_utils.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/12/14 18:30:23 by jboeve        #+#    #+#                 */
/*   Updated: 2023/12/20 18:41:08 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include <math.h>

t_vec2d vec2d_add(t_vec2d v1, t_vec2d v2)
{
	t_vec2d	sum;

	sum.x = v1.x + v2.x;
	sum.y = v1.y + v2.y;
	return (sum);
}

t_vec2d	vec2d_scalar_product(t_vec2d vec, double scalar)
{
	return ((t_vec2d){vec.x * scalar, vec.y * scalar});
}

void print_vec2d(char *str, t_vec2d vector)
{
  printf("%s X: %f | Y: %f\n", str, vector.x, vector.y);
}

t_vec2d vec2d_rotate(t_vec2d old, double radiant)
{
	t_vec2d	new;

	new.x = old.x * cos(radiant) - old.y * sin(radiant);
	new.y = old.x * sin(radiant) + old.y * cos(radiant);
	return (new);
}

// t_vec2f	vec2f_normalize(t_vec2f vec)
// {
// 	float m = sqrt(vec[VEC_X] * vec[VEC_X] + vec[VEC_Y] * vec[VEC_Y]);
// 	return (vec / m);
// }
