/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                       :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:27:33 by yzaim         #+#    #+#                 */
/*   Updated: 2024/03/01 14:41:17 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "raycaster.h"

inline static t_side	ray_move(t_vec2d *side_dist, t_vec2d *delta_dist, \
		t_vec2i step_size, t_vec2i *map_pos)
{
	if (side_dist->x < side_dist->y)
	{
		side_dist->x += delta_dist->x;
		map_pos->x += step_size.x;
		if (step_size.x > 0)
			return (SIDE_E);
		else
			return (SIDE_W);
	}
	else
	{
		side_dist->y += delta_dist->y;
		map_pos->y += step_size.y;
		if (step_size.y > 0)
			return (SIDE_S);
		else
			return (SIDE_N);
	}
}

static void	ray_check_door_x_axis(t_ray *r, t_vec2d *side_dist, \
		const t_vec2d delta_dist, const t_vec2i step_size)
{
	if (side_dist->y - (delta_dist.y / 2) < side_dist->x)
		side_dist->y += delta_dist.y / 2;
	else
	{
		side_dist->x += delta_dist.x;
		r->hit_cell = MAP_WALL;
		r->map_pos.x += step_size.x;
		if (step_size.x > 0)
			r->hit_side = (SIDE_E);
		else
			r->hit_side = (SIDE_W);
	}
}

static void	ray_check_door(t_ray *r, t_vec2d *side_dist, \
		const t_vec2d delta_dist, const t_vec2i step_size)
{
	if (r->hit_side == SIDE_N || r->hit_side == SIDE_S)
		ray_check_door_x_axis(r, side_dist, delta_dist, step_size);
	else
	{
		if (side_dist->x - (delta_dist.x / 2) < side_dist->y)
			side_dist->x += delta_dist.x / 2;
		else
		{
			side_dist->y += delta_dist.y;
			r->hit_cell = MAP_WALL;
			r->map_pos.y += step_size.y;
			if (step_size.y > 0)
				r->hit_side = (SIDE_S);
			else
				r->hit_side = (SIDE_N);
		}
	}
}

t_ray	raycaster_cast(t_vec2d pp, t_vec2d dir, t_ray_hitfunc hit, \
		const void *param)
{
	t_ray	r;
	t_vec2i	step_size;
	t_vec2d	side_dist;
	t_vec2d	delta_dist;

	r.direction = dir;
	r.map_pos.x = (int)pp.x;
	r.map_pos.y = (int)pp.y;
	delta_dist = calculate_delta_dist(dir);
	side_dist = calculate_side_dist(dir, pp, r.map_pos, delta_dist);
	step_size = calculate_step_size(dir);
	while (1)
	{
		r.hit_side = ray_move(&side_dist, &delta_dist, step_size, &r.map_pos);
		r.hit_cell = hit(param, r.map_pos.x, r.map_pos.y);
		if (world_is_interactable(r.hit_cell))
			ray_check_door(&r, &side_dist, delta_dist, step_size);
		if (r.hit_cell)
			break;
	}
	r.length = calculate_ray_length(r.hit_side, side_dist, delta_dist);
	// Tmporary to get the end
	r.end = vec2i_to_vec2d(r.map_pos);
	
	r.line_height = (int)(WINDOW_HEIGHT / r.length);

	// draw start and draw end
	r.line_point.x = -r.line_height / 2 + ((double)WINDOW_HEIGHT) / 2;
	r.line_point.y = r.line_height / 2 + ((double)WINDOW_HEIGHT) / 2;

	if (r.hit_side == SIDE_E || r.hit_side == SIDE_W)
		r.wall_x = pp.y + r.length * r.direction.y;
	else
		r.wall_x = pp.x + r.length * r.direction.x;
	r.wall_x -= floor(r.wall_x);
	return (r);
}
