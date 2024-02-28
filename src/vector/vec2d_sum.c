/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec2d_sum.c                                       :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <yzaim@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 16:09:26 by yzaim         #+#    #+#                 */
/*   Updated: 2024/01/19 23:37:30 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

t_vec2d	vec2d_scalar_product(t_vec2d vec, double scalar)
{
	return ((t_vec2d){vec.x * scalar, vec.y * scalar});
}

double	vec2d_dot_product(t_vec2d v1, t_vec2d v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y));
}

t_vec2d	vec2d_mul(t_vec2d v1, t_vec2d v2)
{
	return ((t_vec2d){v1.x * v2.x, v1.y * v2.y});
}
