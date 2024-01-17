/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_viewport.c                                 :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:28:08 by yzaim         #+#    #+#                 */
/*   Updated: 2024/01/17 15:02:31 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "meta.h"
#include <stdint.h>
#include <stdio.h>

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

static void	draw_column1(t_meta *meta, t_vec2i line, t_ray *ray, uint32_t col, uint32_t h)
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
			// color = set_color(row / 1, row / 2, row / 4, 255);
			// color = find_color(meta->attributes.floor_c);
		}
		mlx_put_pixel(meta->image, col, row, color);
		row++;
	}
}

mlx_texture_t	*get_texture(t_side side, t_attr attributes);
#include <math.h>

static void	draw_column(t_meta *meta, t_vec2i line, t_ray *ray, uint32_t col, uint32_t h)
{
	int32_t			color;
	mlx_texture_t	*texture;

	texture = get_texture(ray->hit_side, meta->attributes);

	ray->texture_point.x = (int)(ray->wall_x * (double)texture->width);
	printf("texture_point [%lf]\n", ray->wall_x);


	if ((ray->hit_side == SIDE_N || ray->hit_side == SIDE_S) && ray->direction.x > 0)
	{
		ray->texture_point.x = texture->width - ray->texture_point.x - 1;
	}
	if ((ray->hit_side == SIDE_E || ray->hit_side == SIDE_W) && ray->direction.y < 0)
	{
		ray->texture_point.x = texture->width - ray->texture_point.x - 1;
	}
	ray->step = 1.0 * texture->height / ray->line_height;
	// x is draw start and y is draw end

	ray->texture_position = (ray->line_point.x - (double) (h / 2.0) + ray->line_height / 2.0) * ray->step;

	int32_t row;
	row = 0;
	while (row < (int32_t) h)
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
			ray->texture_point.y = ((int) ray->texture_position) & (texture->height - 1);
			ray->texture_position += ray->step;
			color = pixel_picker(texture, (int)round(ray->texture_point.x), (int)round(ray->texture_point.y));
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
	uint32_t col = 0;
	while(col < image->width)
	{
		// p->rays[i].line_height = calculate_line_height(p->rays[i].length, image->height);
		// t_vec2d line = calculate_line_points(image->height, p->rays[i].line_height);
		
		draw_column(p->meta, p->rays[col].line_point, &p->rays[col], col, image->height);
		col++;
	}
}

