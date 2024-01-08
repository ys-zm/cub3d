/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:27:33 by yzaim             #+#    #+#             */
/*   Updated: 2024/01/08 15:27:37 by yzaim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "vector.h"
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

inline static t_vec2d	calculate_delta_dist(t_vec2d ray_direction)
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

inline static t_vec2d	calculate_side_dist(t_vec2d ray_direction, \
			t_vec2d player_pos, t_vec2d map_pos, t_vec2d delta_dist)
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

inline static t_vec2d	calculate_step_size(t_vec2d ray_direction)
{
	const bool		comp_x = (ray_direction.x < 0);
	const bool		comp_y = (ray_direction.y < 0);
	const int8_t	dir_x = (comp_x * -1) + (!comp_x * 1);
	const int8_t	dir_y = (comp_y * -1) + (!comp_y * 1);

	return ((t_vec2d){dir_x, dir_y});
}

inline static double	calculate_ray_length(t_side hit_side, \
		t_vec2d side_dist, t_vec2d delta_dist)
{
	if (hit_side == HIT_NS)
		return (side_dist.x - delta_dist.x);
	else
		return (side_dist.y - delta_dist.y);
}

inline static t_side	ray_move(t_vec2d *side_dist, t_vec2d *delta_dist, \
		t_vec2d step_size, t_vec2d *map_pos)
{
	if (side_dist->x < side_dist->y)
	{
		side_dist->x += delta_dist->x;
		map_pos->x += step_size.x;
		return (HIT_NS);
	}
	else
	{
		side_dist->y += delta_dist->y;
		map_pos->y += step_size.y;
		return (HIT_EW);
	}
}

t_ray	raycaster_cast(t_vec2d pp, t_vec2d dir, t_ray_hitfunc hit, const void *param)
{
	t_ray	r;
	t_vec2d	map_pos;
	t_vec2d	side_dist;
	t_vec2d	step_size;
	t_vec2d delta_dist;

	map_pos.x = (int)pp.x;
	map_pos.y = (int)pp.y;
	delta_dist = calculate_delta_dist(dir);
	side_dist = calculate_side_dist(dir, pp, map_pos, delta_dist);
	step_size = calculate_step_size(dir);
	size_t limit = 25;
	while (limit)
	{
		r.hit_side = ray_move(&side_dist, &delta_dist, step_size, &map_pos);
		if (hit && hit(param, map_pos.x, map_pos.y))
			break;
		limit--;
	}
	if (!limit)
		WARNING("Raycaster limit reached!");
	r.length = calculate_ray_length(r.hit_side, side_dist, delta_dist);
	r.direction = dir;
	r.end = map_pos;

	if (r.hit_side == HIT_NS)
		r.wall_x = map_pos.y + r.length * r.direction.y;
	else
		r.wall_x = map_pos.x + r.length * r.direction.x;
	r.wall_x -= floor(r.wall_x);
	return (r);
}
