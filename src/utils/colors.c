/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 22:35:05 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/14 17:45:59 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include <math.h>

int32_t set_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

mlx_texture_t	*get_texture(t_side side, t_tex tex)
{
	if (side == HIT_N)
		return (tex.n);
	else if (side == HIT_S)
		return (tex.s);
	else if (side == HIT_E)
		return (tex.e);
	return (tex.w);
}

void	wall_texture_position(t_ray_data *data, mlx_texture_t *texture, uint32_t h)
{
	// printf("wall x: %f\n", ray->wall_x);
	data->texture_point.x = (int)(data->wall_x * (double)texture->width);
	if ((data->side == HIT_N || data->side == HIT_S) && data->ray_direction.x > 0)
	{
		data->texture_point.x = texture->width - data->texture_point.x - 1;
	}
	if ((data->side == HIT_E || data->side == HIT_W) && data->ray_direction.y > 0)
	{
		data->texture_point.x = texture->width - data->texture_point.x - 1;
	}
	data->progress = 1.0 * texture->height / data->line_height;
	data->texture_position = (data->start + (data->line_height - h)/ 2) * data->progress;
}


uint32_t	pixel_picker(mlx_texture_t *texture, int32_t x, int32_t y)
{
	int32_t	r;
	int32_t	g;
	int32_t	b;
	int32_t	a;
	int32_t	index;

	// printf("x: %u | y: %u\n", x, y);
	index = y * texture->width * 4 + x * 4;
	r = (int32_t)texture->pixels[index];
	g = (int32_t)texture->pixels[index + 1];
	b = (int32_t)texture->pixels[index + 2];
	a = (int32_t)texture->pixels[index + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

int32_t find_wall_color(t_meta *meta)
{
	t_ray_data	*data = &meta->player.data;
	uint32_t	color = 0;
	mlx_texture_t	*texture = get_texture(meta->player.data.side, meta->tex);

	data->texture_point.y = (int)data->texture_position & (texture->height - 1);
	data->texture_position += data->progress;
	color = pixel_picker(texture, (int)round(data->texture_point.x), (int) round(data->texture_point.y));
	return (color);
}