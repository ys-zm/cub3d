/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   raycaster_init.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/03/01 12:58:07 by jboeve        #+#    #+#                 */
/*   Updated: 2024/03/01 13:09:52 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

t_vec2d	calculate_delta_dist(t_vec2d ray_direction)
{
	t_vec2d			delta_dist;
	const double	tolerance = 0.005;

	if (fabs(-ray_direction.x) < tolerance)
		delta_dist.x = INT32_MAX;
	else
		delta_dist.x = fabs(1 / ray_direction.x);
	if (fabs(-ray_direction.y) < tolerance)
		delta_dist.y = INT32_MAX;
	else
		delta_dist.y = fabs(1 / ray_direction.y);
	return (delta_dist);
}

t_vec2d	calculate_side_dist(t_vec2d ray_direction, \
			t_vec2d player_pos, t_vec2i map_pos, t_vec2d delta_dist)
{
	t_vec2d	side_dist;

	if (ray_direction.x < 0)
		side_dist.x = (player_pos.x - map_pos.x) * delta_dist.x;
	else
		side_dist.x = (map_pos.x + 1.0 - player_pos.x) * delta_dist.x;
	if (ray_direction.y < 0)
		side_dist.y = (player_pos.y - map_pos.y) * delta_dist.y;
	else
		side_dist.y = (map_pos.y + 1.0 - player_pos.y) * delta_dist.y;
	return (side_dist);
}

t_vec2i	calculate_step_size(t_vec2d ray_direction)
{
	const bool		comp_x = (ray_direction.x < 0);
	const bool		comp_y = (ray_direction.y < 0);
	const int8_t	dir_x = (comp_x * -1) + (!comp_x * 1);
	const int8_t	dir_y = (comp_y * -1) + (!comp_y * 1);

	return ((t_vec2i){dir_x, dir_y});
}

double	calculate_ray_length(t_side hit_side, \
		t_vec2d side_dist, t_vec2d delta_dist)
{
	if (hit_side == SIDE_E || hit_side == SIDE_W)
		return (side_dist.x - delta_dist.x);
	else
		return (side_dist.y - delta_dist.y);
}
