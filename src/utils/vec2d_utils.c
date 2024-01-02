/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   vec2d_utils.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/12/14 18:30:23 by jboeve        #+#    #+#                 */
/*   Updated: 2024/01/02 21:26:28 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "vector.h"
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

t_vec2d	vec2d_mul(t_vec2d v1, t_vec2d v2)
{
	return ((t_vec2d){v1.x * v2.x, v1.y * v2.y});
}

void print_vec2d(char *str, t_vec2d vector)
{
 	printf("%s X: %lf | Y: %lf\n", str, vector.x, vector.y);
}

t_vec2d vec2d_rotate(t_vec2d old, double radiant)
{
	t_vec2d	new;

	new.x = old.x * cos(radiant) - old.y * sin(radiant);
	new.y = old.x * sin(radiant) + old.y * cos(radiant);
	return (new);
}

t_vec2d vec2u_to_vec2d(t_vec2u v)
{
	return (t_vec2d) {v.x, v.y};
}

double deg_to_rad(float deg)
{
	return deg * (PI / 180);
}

t_vec2d	vec2d_normalize(t_vec2d vec)
{
	float m = sqrt(vec.x * vec.x + vec.y * vec.y);
	return ((t_vec2d) {vec.x / m, vec.y / m});
}
