/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <yzaim@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 16:09:11 by yzaim         #+#    #+#                 */
/*   Updated: 2024/01/08 16:09:14 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include <stdio.h>
#include <math.h>

int32_t set_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

// int32_t find_wall_color(t_side side)
// {
// 	int32_t color;

// 	if (side == SIDE_N || side == SIDE_S)
// 	{
// 		color = VIEWPORT_COLOR_WALL_NS;
// 	}
// 	else
// 	{
// 		color = VIEWPORT_COLOR_WALL_EW;
// 	}
// 	return (color);
// }

mlx_texture_t	*get_texture(t_side side, t_attr attributes)
{
	if (side == SIDE_N)
		return (attributes.n.tex);
	else if (side == SIDE_S)
		return (attributes.s.tex);
	else if (side == SIDE_E)
		return (attributes.e.tex);
	return (attributes.w.tex);
}

int32_t	find_wall_color(t_attr atrributes, t_ray *ray, t_vec2d line_points, uint32_t h)
{
	int32_t			color;
	mlx_texture_t	*texture;

	texture = get_texture(ray->hit_side, atrributes);
	wall_texture_position(texture, ray, line_points, h);
	ray->texture_point.y = (int)ray->texture_position & (texture->height - 1);
	ray->texture_position += ray->step;
	color = pixel_picker(texture, (int)round(ray->texture_point.x), (int)round(ray->texture_point.y));
	return (color);
}

int32_t	find_color(t_rgba rgba)
{
	int32_t	color;

	color = set_color(rgba.r, rgba.g, rgba.b, rgba.a);
	return (color);
}