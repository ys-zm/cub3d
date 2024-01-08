/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_viewport.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:28:08 by yzaim         #+#    #+#                 */
/*   Updated: 2024/01/08 16:13:27 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"

static t_vec2d	calculate_line_points(double ray_length, uint32_t h)
{
	//calculate lowest and highest pixel to fill in current stripe
	uint32_t	start;
	uint32_t	end;
	double		line_height;

	line_height = (int)(h / ray_length);
	if (line_height > h)
		line_height = h;
	start = -line_height / 2 + ((double)h) / 2;
	end = line_height / 2 + ((double)h) / 2;
	if (end >= h)
		end = h - 1;
	return ((t_vec2d) {start, end});
}

static void	draw_column(t_meta *meta, t_vec2d line, t_side side, uint32_t col, uint32_t h)
{
	uint32_t	color;
	uint32_t	row;

	row = 0;
	while (row < h)
	{
		// ceiling
		if (row < line.x)
			color = VIEWPORT_COLOR_CEILING;
		// floor
		else if (row > line.y)
			color = VIEWPORT_COLOR_FLOOR;
		else
		{
			color = find_wall_color(side);
		}
		mlx_put_pixel(meta->image, col, row, color);
		row++;
	}
}

void render_viewport(mlx_image_t *image, t_player *p)
{
	uint32_t i = 0;
	while(i < image->width)
	{
		t_vec2d line = calculate_line_points(p->rays[i].length, image->height);
		draw_column(p->meta, line, p->rays[i].hit_side, i, image->height);
		i++;
	}
}

