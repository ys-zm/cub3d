/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_func.c                                       :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:28:08 by yzaim         #+#    #+#                 */
/*   Updated: 2024/06/03 18:29:46 by yesimzaim     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "libft.h"
#include "meta.h"
#include "vector.h"
#include <stdint.h>
#include <stdio.h>
#include <math.h>

static void	calculate_texture_points(mlx_texture_t *texture, t_ray *ray, uint32_t h)
{
	double	offset;

	offset = 0;
	ray->texture_point.x = (int)(ray->wall_x * texture->width);
	if ((ray->hit_side == SIDE_E || ray->hit_side == SIDE_W) && ray->direction.x > 0)
		ray->texture_point.x = texture->width - ray->texture_point.x - 1;
	if ((ray->hit_side == SIDE_S || ray->hit_side == SIDE_N) && ray->direction.y < 0)
		ray->texture_point.x = texture->width - ray->texture_point.x - 1;
	if (ray->line_height > h)
		offset = (ray->line_height - h) / 2;
	ray->step = ((double) texture->height) / (double) ray->line_height;
	ray->texture_position = (ray->line_point.x - (float)h / 2 + (float)ray->line_height / 2) * ray->step;
}

void	draw_column(t_meta *meta, t_ray *ray, uint32_t col, uint32_t h)
{
	int32_t			y;
	int32_t			color;
	mlx_texture_t	*texture;

	texture = get_texture(ray->hit_cell, ray->hit_side, meta->attributes);
	calculate_texture_points(texture, ray, h);
	y = ray->line_point.x;
	while (y < ray->line_point.y && y < (int32_t)WINDOW_HEIGHT)
	{
		ray->texture_point.y = ((int) ray->texture_position);
		ray->texture_position += ray->step;
		color = pixel_picker(texture, (int)round(ray->texture_point.x), (int)round(ray->texture_point.y));
		if (y >= 0)
			mlx_put_pixel(meta->image, col, y, color);
		y++;
	}
}

void	draw_floor(mlx_image_t *image, t_vray *vray, t_attr *attributes, t_vec2i pos)
{
	const t_vec2i	cell = vec2d_to_vec2i(vray->floor);
	mlx_texture_t	*f_tex;
	t_vec2i			f_t;

	f_tex = attributes->f.tex;
	if (f_tex)
	{
		f_t.x = (int)(f_tex->width * (vray->floor.x - cell.x)) & (f_tex->width - 1);
		f_t.y = (int)(f_tex->height * (vray->floor.y - cell.y)) & (f_tex->height - 1);
		mlx_put_pixel(image, pos.y, pos.x, pixel_picker(f_tex, f_t.x, f_t.y));
	}
	else
	{
		mlx_put_pixel(image, pos.y, pos.x, find_color(attributes->floor_c));
	}
}

static int32_t	col_ceiling_tex(mlx_texture_t *tex, t_vray *vray, t_vec2i cell)
{
	t_vec2i			c_t;

	c_t.x = (int)(tex->width * (vray->floor.x - cell.x)) & (tex->width - 1);
	c_t.y = (int)(tex->height * (vray->floor.y - cell.y)) & (tex->height - 1);
	return (pixel_picker(tex, c_t.x, c_t.y));
}

void	draw_ceil(mlx_image_t *image, t_vray *vray, t_attr *attributes, t_vec2i pos)
{
	const t_vec2i	cell = vec2d_to_vec2i(vray->floor);
	mlx_texture_t	*c_tex;
	mlx_texture_t	*c_alt_tex;

	c_tex = attributes->c.tex;
	c_alt_tex = attributes->c_alt.tex;
	if (cell.y % 2 && cell.x % 2 && (c_alt_tex || attributes->ceil_alt_c.a))
	{
		if (c_alt_tex)
			mlx_put_pixel(image, pos.y, WINDOW_HEIGHT - pos.x - 1, col_ceiling_tex(c_alt_tex, vray, cell));
		else if (attributes->ceil_alt_c.a)
			mlx_put_pixel(image, pos.y, WINDOW_HEIGHT - pos.x - 1, find_color(attributes->ceil_alt_c));
	}
	else
	{
		if (c_tex)
			mlx_put_pixel(image, pos.y, WINDOW_HEIGHT - pos.x - 1, col_ceiling_tex(c_tex, vray, cell));
		else
			mlx_put_pixel(image, pos.y, WINDOW_HEIGHT - pos.x - 1, find_color(attributes->ceiling_c));
	}
}
