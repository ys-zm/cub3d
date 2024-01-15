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

static t_vec2d	calculate_line_points(uint32_t h, double line_height)
{
	//calculate lowest and highest pixel to fill in current stripe
	uint32_t	start;
	uint32_t	end;

	start = -line_height / 2 + ((double)h) / 2;
	end = line_height / 2 + ((double)h) / 2;
	if (end >= h)
		end = h - 1;
	return ((t_vec2d) {start, end});
}

static void	draw_column(t_meta *meta, t_vec2d line, t_ray *ray, uint32_t col, uint32_t h)
{
	uint32_t	color;
	uint32_t	row;

	row = 0;
	
	while (row < h)
	{
		// ceiling
		if (row < line.x)
		{
				color = find_color(meta->attributes.ceiling_c);
		}
		// floor
		else if (row > line.y)
		{
			color = find_color(meta->attributes.floor_c);
		}
		else
		{
			color = find_wall_color(meta->attributes, ray, line, h);
		}
		mlx_put_pixel(meta->image, col, row, color);
		row++;
	}
}

double	calculate_line_height(double ray_length, uint32_t h)
{
	double		line_height;

	line_height = (int)(h / ray_length);
	if (line_height > h)
		line_height = h;
	return (line_height);
}

void render_viewport(mlx_image_t *image, t_player *p)
{
	uint32_t i = 0;
	while(i < image->width)
	{
		// p->rays[i].line_height = calculate_line_height(p->rays[i].length, image->height);
		// t_vec2d line = calculate_line_points(image->height, p->rays[i].line_height);
		
		draw_column(p->meta, p->rays[i].line_point, &p->rays[i], i, image->height);
		i++;
	}
}

