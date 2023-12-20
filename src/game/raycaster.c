/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   raycaster.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/12/15 15:20:09 by jboeve        #+#    #+#                 */
/*   Updated: 2023/12/20 15:59:20 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "meta.h"
#include <math.h>

void	calculate_delta_dist(t_player *player)
{
	t_ray_data* const data = &player->data;

	if (data->ray_direction.x == 0)
	{
		data->delta_distance.x = INT32_MAX;
	}
	else
	{
		data->delta_distance.x = fabs(1 / data->ray_direction.x);
	}
	if (data->ray_direction.y == 0)
	{
		data->delta_distance.y = INT32_MAX;
	}
	else
	{
		data->delta_distance.y = fabs(1 / data->ray_direction.y);
	}
}

void	calculate_side_distance(t_player *player)
{
	t_ray_data* const data = &player->data;

	if (data->ray_direction.x < 0)
	{
		data->step.x = -1;
		data->side_distance.x = (player->position.x - data->map_pos.x) * data->delta_distance.x;
	}
	else
	{
		data->step.x = 1;
		data->side_distance.x = (data->map_pos.x + 1.0 - player->position.x) * data->delta_distance.x;
	}
	if (data->ray_direction.y < 0)
	{
		data->step.y = -1;
		data->side_distance.y = (player->position.y - data->map_pos.y) * data->delta_distance.y;
	}
	else
	{
		data->step.y = 1;
		data->side_distance.y = (data->map_pos.y + 1.0 - player->position.y) * data->delta_distance.y;
	}
}

void	dda_algorithm(t_meta *meta)
{
	t_ray_data* const data = &meta->player.data;
	data->hit = false;

	while (data->hit == false)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if (data->side_distance.x < data->side_distance.y)
		{
			data->side_distance.x += data->delta_distance.x;
			data->map_pos.x += data->step.x;
			data->side = HIT_NS;
		}
		else
		{
			data->side_distance.y += data->delta_distance.y;
			data->map_pos.y += data->step.y;
			data->side = HIT_EW;
		}
		//Check if ray has hit a wall
		if (data->map_pos.x >= 0 && data->map_pos.y >= 0 && data->map_pos.x < meta->map.width && data->map_pos.y < meta->map.height)
		{
			if (meta->map.level[find_index(meta, data->map_pos.x, data->map_pos.y)] == MAP_WALL)
			{
				data->hit = true;
			}
		}
		else
		{
			UNIMPLEMENTED("Map out of bounds.");
		}
	}
}

void	calculate_line_height(t_ray_data *data, int h)
{	
	//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
	if(data->side == HIT_NS)
	{
		data->perp_wall_distance = (data->side_distance.x - data->delta_distance.x);
	}
	else
	{
		data->perp_wall_distance = (data->side_distance.y - data->delta_distance.y);
	} 
	//Calculate height of line to draw on screen
	data->line_height = (int)(h / data->perp_wall_distance);
	if (data->line_height > WINDOW_HEIGHT)
	{
		data->line_height = WINDOW_HEIGHT;
	}
}

void	calculate_draw_start_and_end(t_meta *meta, uint32_t h)
{
	//calculate lowest and highest pixel to fill in current stripe
	t_ray_data* const data = &meta->player.data;

	data->start = -data->line_height / 2 + h / 2;
	if (data->start < 0)
	{
		data->start = 0;
	}
	data->end = data->line_height / 2 + h / 2;
	if (data->end >= h)
	{
		data->end = h - 1;
	}
}

void	draw_column(t_meta *meta, uint32_t col, uint32_t h)
{
	uint32_t    color;
	uint32_t    row;
	t_ray_data  const data = meta->player.data;

	row = 0;
	// draw_col(meta->image, start, end, color);
	while (row < h)
	{
		// ceiling
		if (row < data.start)
		{
			color = set_color(0, 0, 0, 255);
		}
		// floor
		else if (row > data.end)
		{
			color = set_color(255, 255, 255, 255);
		}
		else
		{
			color = find_wall_color(data.side);
		} 
		mlx_put_pixel(meta->image, col, row, color);
		row++;
	}
}
