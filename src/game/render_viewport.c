/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_viewport.c                                 :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:28:08 by yzaim         #+#    #+#                 */
/*   Updated: 2024/01/17 23:59:00 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "meta.h"
#include <stdint.h>
#include <stdio.h>
#include <math.h>

mlx_texture_t	*get_texture(t_side side, t_attr attributes);

static void	draw_column(t_meta *meta, t_vec2i line, t_ray *ray, uint32_t col, uint32_t h)
{
	int32_t			y;
	int32_t			color;
	mlx_texture_t	*texture;

	texture = get_texture(ray->hit_side, meta->attributes);

	ray->texture_point.x = (int)(ray->wall_x * texture->width);
	if ((ray->hit_side == SIDE_N || ray->hit_side == SIDE_S) && ray->direction.x > 0)
		ray->texture_point.x = texture->width - ray->texture_point.x - 1;
	if ((ray->hit_side == SIDE_E || ray->hit_side == SIDE_W) && ray->direction.y < 0)
		ray->texture_point.x = texture->width - ray->texture_point.x - 1;

	ray->step = 1.0 * texture->height / ray->line_height;
	ray->texture_position = (ray->line_point.x + (ray->line_height - h) / 2) * ray->step;

	y = 0;
	while (y < (int32_t) h)
	{
		if (y < line.x)
			color = find_color(meta->attributes.ceiling_c);
		else if (y > line.y)
			color = find_color(meta->attributes.floor_c);
		else
		{
			ray->texture_point.y = ((int) ray->texture_position) & (texture->height - 1);
			ray->texture_position += ray->step;
			color = pixel_picker(texture, (int)round(ray->texture_point.x), (int)round(ray->texture_point.y));
		}
		mlx_put_pixel(meta->image, col, y, color);
		y++;
	}
}

void render_viewport(mlx_image_t *image, t_player *p)
{
	uint32_t col = 0;
	while(col < image->width)
	{
		draw_column(p->meta, p->rays[col].line_point, &p->rays[col], col, image->height);
		col++;
	}
}

