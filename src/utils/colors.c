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

t_tex	get_texture(t_side side, t_attr attributes)
{
	if (side == SIDE_N)
		return (attributes.n);
	else if (side == SIDE_S)
		return (attributes.s);
	else if (side == SIDE_E)
		return (attributes.e);
	return (attributes.w);
}

int32_t	find_wall_color(t_attr atrributes, t_ray *ray, t_vec2d line_points, uint32_t h)
{
	int32_t		color;
	t_tex		texture;

	texture = get_texture(ray->hit_side, atrributes);
	wall_texture_position(texture, ray, line_points, h);
	ray->texture.y = (int)ray->texture_position & (texture.tex->height - 1);
	ray->texture_position += ray->step;
	printf("h: %d\n",h);
	// printf("texture position: %f\n", ray->texture_position);
	// printf("x: %d | y: %d\n", ray->texture.x, ray->texture.y);
	color = pixel_picker(texture, ray->texture.x, ray->texture.y);
	return (color);
}

int32_t	find_color(t_rgba rgba)
{
	int32_t	color;

	color = set_color(rgba.r, rgba.g, rgba.b, rgba.a);
	return (color);
}