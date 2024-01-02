/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   raycaster.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/12/15 15:20:09 by jboeve        #+#    #+#                 */
/*   Updated: 2024/01/02 17:04:23 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "meta.h"
#include "parser.h"
#include <math.h>
#include <stdint.h>

static t_vec2d calculate_delta_dist1(t_vec2d ray_direction)
{
	t_vec2d delta_dist;

	if (ray_direction.x == 0)
	{
		delta_dist.x = INT32_MAX;
	}
	else
	{
		delta_dist.x = fabs(1 / ray_direction.x);
	}
	if (ray_direction.y == 0)
	{
		delta_dist.y = INT32_MAX;
	}
	else
	{
		delta_dist.y = fabs(1 / ray_direction.y);
	}
	return (delta_dist);
}

static t_vec2d	calculate_side_distance1(t_vec2d ray_direction, t_vec2d player_pos, t_vec2d map_pos, t_vec2d delta_dist, t_vec2d *step)
{
	t_vec2d side_dist;

	if (ray_direction.x < 0)
	{
		step->x = -1;
		side_dist.x = (player_pos.x - map_pos.x) * delta_dist.x;
	}
	else
	{
		step->x = 1;
		side_dist.x = (map_pos.x + 1.0 - player_pos.x) * delta_dist.x;
	}
	if (ray_direction.y < 0)
	{
		step->y = -1;
		side_dist.y = (player_pos.y - map_pos.y) * delta_dist.y;
	}
	else
	{
		step->y = 1;
		side_dist.y = (map_pos.y + 1.0 - player_pos.y) * delta_dist.y;
	}
	return side_dist;
}

static double	calculate_wall_dist1(t_side hit_side, t_vec2d side_dist, t_vec2d delta_dist);

static t_ray	dda_algorithm1(t_meta *meta, t_vec2d player_pos, t_vec2d ray_direction,t_ray_hitfunc has_hit)
{
	t_ray ray;
	t_vec2d	map_pos;
	t_vec2d	tmp_step;

	t_vec2d delta_dist = calculate_delta_dist1(ray_direction);
	map_pos.x = (int)player_pos.x;
	map_pos.y = (int)player_pos.y;
	t_vec2d side_dist = calculate_side_distance1(ray_direction, player_pos, map_pos, delta_dist, &tmp_step);

	bool hit = false;
	while (!hit)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			map_pos.x += tmp_step.x;
			ray.hit_side = HIT_NS;
		}
		else
		{
			side_dist.y += delta_dist.y;
			map_pos.y += tmp_step.y;
			ray.hit_side = HIT_EW;
		}
		hit = has_hit(meta, map_pos.x, map_pos.y);
	}
	ray.length = calculate_wall_dist1(ray.hit_side, side_dist, delta_dist);
	return (ray);
}

static double	calculate_wall_dist1(t_side hit_side, t_vec2d side_dist, t_vec2d delta_dist)
{	
	double		perp_wall_dist;

	//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
	if (hit_side == HIT_NS)
		perp_wall_dist = (side_dist.x - delta_dist.x);
	else
		perp_wall_dist = (side_dist.y - delta_dist.y);

	return (perp_wall_dist);
}

t_vec2d	calculate_draw_start_and_end1(double ray_length, uint32_t h)
{
	//calculate lowest and highest pixel to fill in current stripe
	uint32_t	start;
	uint32_t	end;
	double	line_height = (int)(h / ray_length);
	if (line_height > h)
		line_height = h;

	start = -line_height / 2 + h / 2;
	if (start < 0)
	{
		start = 0;
	}
	end = line_height / 2 + h / 2;
	if (end >= h)
	{
		end = h - 1;
	}
	t_vec2d line;
	line.x = start;
	line.y = end;
	return line;
}

void	draw_column1(t_meta *meta, t_vec2d line, t_side side, uint32_t col, uint32_t h)
{
	uint32_t    color;
	uint32_t    row;

	row = 0;
	// draw_col(meta->image, start, end, color);
	while (row < h)
	{
		// ceiling
		if (row < line.x)
		{
			color = set_color(0, 0, 0, 255);
		}
		// floor
		else if (row > line.y)
		{
			color = set_color(255, 255, 255, 255);
		}
		else
		{
			color = find_wall_color(side);
		} 
		mlx_put_pixel(meta->image, col, row, color);
		row++;
	}
}



t_ray raycaster_cast(t_meta *meta, t_vec2d player_pos, t_vec2d ray_direction, t_ray_hitfunc has_hit)
{
	t_ray	ray;

	ray = dda_algorithm1(meta, player_pos, ray_direction, has_hit);

	return ray;
}
