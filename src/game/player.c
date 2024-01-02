/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   player.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/10 02:25:34 by joppe         #+#    #+#                 */
/*   Updated: 2024/01/02 17:40:38 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "libft.h"
#include "meta.h"
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool	out_of_bounds(t_meta *meta, int x, int y)
{
	if (x < 0 || y < 0 || x >= (int)meta->map.width || y >= (int)meta->map.height)
		return (true);
	return (false);
}

// detects the hit too late
static bool if_hits_wall(t_meta *meta, uint32_t x, uint32_t y)
{
	if (out_of_bounds(meta, x, y))
		return true;
	if (meta->map.level[find_index(meta, x, y)] == MAP_WALL)
	{
		return (true);
	}
	return (false);
}

bool bound_check(void *param, uint32_t x, uint32_t y)
{
	t_meta *const meta = (t_meta *) param;
	if (x >= 0 && y >= 0 && x < meta->map.width && y < meta->map.height)
		return (meta->map.level[find_index(meta, x, y)] == MAP_WALL);
	else
	{
		UNIMPLEMENTED("Map out of bounds.");
	}
}

void player_move(t_meta *meta, t_vec2d transform)
{
	t_player* const	p = &meta->player;
	t_vec2d			new_position;

	new_position.x = (p->position.x + (transform.x));
	new_position.y = (p->position.y + (transform.y));
	if (!if_hits_wall(meta, new_position.x, new_position.y))
	{
		p->position.x += transform.x;
		p->position.y += transform.y;
	}
}

// negative rotation parameter turns left vs positive rotation parameter turns right
void player_turn(t_meta *meta, float radiant)
{
	meta->player.direction = vec2d_rotate(meta->player.direction, radiant);
	meta->player.plane = vec2d_rotate(meta->player.plane, radiant);
}


// tmp placed here
t_vec2d	calculate_draw_start_and_end1(double ray_length, uint32_t h)
{
	//calculate lowest and highest pixel to fill in current stripe
	uint32_t	start;
	uint32_t	end;
	double		line_height;

	line_height = (int)(h / ray_length);
	if (line_height > h)
		line_height = h;
	start = -line_height / 2 + h / 2;
	if (start < 0)
		start = 0;
	end = line_height / 2 + h / 2;
	if (end >= h)
		end = h - 1;
	return ((t_vec2d) {start, end});
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


void player_raycast(t_player *p)
{
	// TODO Image.width
	uint32_t w = WINDOW_WIDTH;
	uint32_t h = WINDOW_HEIGHT;
	uint32_t col;

	double	camera_x;
	t_vec2d	ray_start;


	// TODO Just create the player.plane here instead of saving it.
	col = 0;
	while(col < w)
	{
		camera_x = (2 * col / ((double) w) - 1);
		ray_start = vec2d_add(p->direction, vec2d_scalar_product(p->plane, camera_x));
		t_ray r = raycaster_cast(p->meta, p->position, ray_start, bound_check);

		t_vec2d line = calculate_draw_start_and_end1(r.length, h);
		draw_column1(p->meta, line, r.hit_side, col, h);

		col++;
	}
}
