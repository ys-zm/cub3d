/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   vec2i.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/01/03 17:52:20 by joppe         #+#    #+#                 */
/*   Updated: 2024/01/03 17:54:33 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec2i	vec2i_scalar_product(t_vec2i vec, double scalar)
{
	return ((t_vec2i){vec.x * scalar, vec.y * scalar});
}

t_vec2i	vec2i_mul(t_vec2i v1, t_vec2i v2)
{
	return ((t_vec2i){v1.x * v2.x, v1.y * v2.y});
}

t_vec2i vec2i_add(t_vec2i v1, t_vec2i v2)
{
	return ((t_vec2i){v1.x + v2.x, v1.y + v2.y});
}
