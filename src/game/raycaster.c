/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                       :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:27:33 by yzaim         #+#    #+#                 */
/*   Updated: 2024/02/12 01:20:13 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "meta.h"
#include "parser.h"
#include "test_utils.h"
#include "vector.h"
#include <math.h>
#include <stdbool.h>
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

inline static t_vec2i	calculate_step_size(t_vec2d ray_direction)
{
	const bool		comp_x = (ray_direction.x < 0);
	const bool		comp_y = (ray_direction.y < 0);
	const int8_t	dir_x = (comp_x * -1) + (!comp_x * 1);
	const int8_t	dir_y = (comp_y * -1) + (!comp_y * 1);

	return ((t_vec2i){dir_x, dir_y});
}

inline static double	calculate_ray_length(t_side hit_side, \
		t_vec2d side_dist, t_vec2d delta_dist)
{
	if (hit_side == SIDE_E || hit_side == SIDE_W)
		return (side_dist.x - delta_dist.x);
	else
		return (side_dist.y - delta_dist.y);
}

// moving the ray forward in the direction until there is a hit
inline static t_side	ray_move(t_vec2d *side_dist, t_vec2d *delta_dist, t_vec2i step_size, t_vec2i *map_pos)
{
	// Looking in the x-axis
	if (side_dist->x < side_dist->y)
	{
		side_dist->x += delta_dist->x;
		map_pos->x += step_size.x;
		if (step_size.x > 0)
			return (SIDE_E);
		else
			return(SIDE_W);
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

inline static t_vec2d	calculate_delta_dist_true(t_vec2d ray_direction)
{
	t_vec2d			delta_dist;
	const double	tolerance = 0.005;

	if (fabs(-ray_direction.x) < tolerance)
		delta_dist.x = INT32_MAX;
	else
		delta_dist.x = sqrt(1 + (ray_direction.y * ray_direction.y) / (ray_direction.x * ray_direction.x));
	if (fabs(-ray_direction.y) < tolerance)
		delta_dist.y = INT32_MAX;
	else
		delta_dist.y = sqrt(1 + (ray_direction.x * ray_direction.x) / (ray_direction.y * ray_direction.y));
	return (delta_dist);
}

static bool ray_check_door(t_meta *m, t_ray *r, t_vec2d *side_dist, t_vec2d delta_dist, t_ray_hitfunc hit)
{
	t_vec2d map_pos = vec2i_to_vec2d(r->map_pos);

	t_vec2d	step_size = vec2d_mul(vec2i_to_vec2d(calculate_step_size(r->direction)), (t_vec2d) {0.5, 0.5});
	t_cell_type hit_cell = hit(m, (uint32_t) map_pos.x, (uint32_t) map_pos.y);

	// While in door tile.
	if (world_is_interactable(hit_cell))
	{
		// if looking in x-axis
		if (side_dist->x < side_dist->y)
		{
			side_dist->x += delta_dist.x;
			map_pos.x += step_size.x;

			m->test_ids[r->id] = true;
		}
		else
		{
			side_dist->y += delta_dist.y;
			map_pos.y += step_size.y;
		}



		hit_cell = hit(m, (uint32_t) map_pos.x, (uint32_t) map_pos.y);

		if (world_is_interactable(hit_cell))
		{
			if (r->id == WINDOW_WIDTH / 2)
				printf("hitting door\n");
			return true;	
		}
		else
		{
			return false;	
		}
	}
	return false;	
}


t_ray	raycaster_cast_id(uint32_t id, t_vec2d pp, t_vec2d dir, t_ray_hitfunc hit, const void *param)
{
	t_ray	r;
	t_vec2i	step_size;
	// Distance from player_pos inside tile to edge of tile.
	t_vec2d	side_dist;
	t_vec2d delta_dist;

	bool hit_door = false;

	r.id = id;
	r.map_pos.x = (int)pp.x;
	r.map_pos.y = (int)pp.y;
	delta_dist = calculate_delta_dist(dir);
	side_dist = calculate_side_dist(dir, pp, r.map_pos, delta_dist);
	step_size = calculate_step_size(dir);
	while (1 && !hit_door)
	{
		r.hit_side = ray_move(&side_dist, &delta_dist, step_size, &r.map_pos);
		r.hit_cell = hit(param, r.map_pos.x, r.map_pos.y);

		if (world_is_interactable(r.hit_cell))
			if (ray_check_door((t_meta *) param, &r, &side_dist, delta_dist, hit))
			{
				hit_door = true;
			}



		
		// Tmporary to get the end
		r.end = vec2i_to_vec2d(r.map_pos);
		if (hit && r.hit_cell)
			break;
	}
	r.length = calculate_ray_length(r.hit_side, side_dist, delta_dist);
	r.direction = dir;
	// print_hit_side("side", r.hit_side);


		if (r.id == WINDOW_WIDTH / 2)
			print_direction(r.hit_side);
	

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









t_ray	raycaster_cast(t_vec2d pp, t_vec2d dir, t_ray_hitfunc hit, const void *param)
{
	t_ray	r;
	t_vec2i	step_size;
	// Distance from player_pos inside tile to edge of tile.
	t_vec2d	side_dist;
	t_vec2d delta_dist;

	r.map_pos.x = (int)pp.x;
	r.map_pos.y = (int)pp.y;
	delta_dist = calculate_delta_dist(dir);
	side_dist = calculate_side_dist(dir, pp, r.map_pos, delta_dist);
	step_size = calculate_step_size(dir);
	size_t limit = 25;
	while (limit)
	{
		r.hit_side = ray_move(&side_dist, &delta_dist, step_size, &r.map_pos);
		r.hit_cell = hit(param, r.map_pos.x, r.map_pos.y);

		// Tmporary to get the end
		r.end = vec2i_to_vec2d(r.map_pos);
		if (hit && r.hit_cell)
			break;
		limit--;
	}
	if (!limit)
		WARNING("Raycaster limit reached!");
	r.length = calculate_ray_length(r.hit_side, side_dist, delta_dist);
	r.direction = dir;
	

	r.line_height = (int)(WINDOW_HEIGHT / r.length);

	// draw start and draw end
	r.line_point.x = -r.line_height / 2 + ((double)WINDOW_HEIGHT) / 2;
	r.line_point.y = r.line_height / 2 + ((double)WINDOW_HEIGHT) / 2;

	if (r.hit_side == SIDE_N || r.hit_side == SIDE_S)
		r.wall_x = pp.y + r.length * r.direction.y;
	else
		r.wall_x = pp.x + r.length * r.direction.x;
	r.wall_x -= floor(r.wall_x);
	return (r);
}
