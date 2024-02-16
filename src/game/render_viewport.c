/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_viewport.c                                 :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:28:08 by yzaim         #+#    #+#                 */
/*   Updated: 2024/02/16 21:56:30 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "libft.h"
#include "meta.h"
#include "vector.h"
#include <stdint.h>
#include <stdio.h>
#include <math.h>


static void	draw_column(t_meta *meta, t_ray *ray, uint32_t col, uint32_t h)
{
	int32_t			y;
	int32_t			color;
	mlx_texture_t	*texture;

	texture = get_texture(ray->hit_cell, ray->hit_side, meta->attributes);

	ray->texture_point.x = (int)(ray->wall_x * texture->width);
	if ((ray->hit_side == SIDE_E || ray->hit_side == SIDE_W) && ray->direction.x > 0)
		ray->texture_point.x = texture->width - ray->texture_point.x - 1;
	if ((ray->hit_side == SIDE_S || ray->hit_side == SIDE_N) && ray->direction.y < 0)
		ray->texture_point.x = texture->width - ray->texture_point.x - 1;
	
	double offset = 0;
	if (ray->line_height > h)
		offset = (ray->line_height - h) / 2;

	ray->step = texture->height / ray->line_height;
	ray->texture_position = ((ray->line_point.x + offset) + (ray->line_height - h) / 2) * ray->step;

	y = 0;
	while (y < (int32_t) h)
	{
		if (y < ray->line_point.x)
			color = find_color(meta->attributes.ceiling_c);
		else if (y >= ray->line_point.y)
			color = find_color(meta->attributes.floor_c);
		else
		{
			ray->texture_point.y = ((int) ray->texture_position) & (texture->height - 1);
			ray->texture_position += ray->step;
			color = pixel_picker(texture, (int)round(ray->texture_point.x), (int)round(ray->texture_point.y));
			mlx_put_pixel(meta->image, col, y, color);
		}
		y++;
	}
}

void	draw_fc(mlx_image_t *image, t_vray *vray, mlx_texture_t *f_tex, mlx_texture_t *c_tex, mlx_texture_t *c_alt_tex, uint32_t col, uint32_t row)
{
	const t_vec2i	cell = vec2d_to_vec2i(vray->floor);
	// coordinate of pixel in texture
	const t_vec2i	c_t = (t_vec2i){(int)(c_tex->width  * (vray->floor.x - cell.x)) & (c_tex->width - 1), 
									(int)(c_tex->height * (vray->floor.y - cell.y)) & (c_tex->height - 1)};
	const t_vec2i	f_t = (t_vec2i){(int)(f_tex->width  * (vray->floor.x - cell.x)) & (f_tex->width - 1),
				 					(int)(f_tex->height * (vray->floor.y - cell.y)) & (f_tex->height - 1)};

	const uint32_t	c_pixel = pixel_picker(c_tex, c_t.x, c_t.y);
	const uint32_t	c_alt_pixel = pixel_picker(c_alt_tex, c_t.x, c_t.y);
	const uint32_t	f_pixel = pixel_picker(f_tex, f_t.x, f_t.y);

	vray->floor = vec2d_add(vray->floor, vray->step);

	if (cell.y % 2 && cell.x % 2)
		mlx_put_pixel(image, col, WINDOW_HEIGHT - row - 1, c_alt_pixel);
	else
		mlx_put_pixel(image, col, WINDOW_HEIGHT - row - 1, c_pixel);

	mlx_put_pixel(image, col, row, f_pixel);
}

void render_viewport(mlx_image_t *image, t_player *p)
{
	uint32_t	col = 0;
	uint32_t	row = 0;


	// render floor and ceiling
	if (p->should_render)
	{
		while (row < image->height)
		{
			col = 0;
			while (col < image->width)
			{
				draw_fc(p->meta->image, &p->vrays[row], p->meta->attributes.f.tex, p->meta->attributes.c.tex, p->meta->attributes.c_alt.tex, col, row);
				col++;
			}
			row++;
		}
		p->should_render = false;
	}

	// render walls	
	col = 0;
	while (col < image->width)
	{
		draw_column(p->meta, &p->hrays[col], col, image->height);
		col++;
	}

	// draw crosshair
	const int32_t crosshair_size = 8;
	draw_rect(image, (WINDOW_WIDTH / 2 - (crosshair_size / 2)), (WINDOW_HEIGHT / 2 - (crosshair_size / 2)), crosshair_size, crosshair_size, 0xFFFFFFFF);
}
