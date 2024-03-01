/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <yzaim@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 16:09:11 by yzaim         #+#    #+#                 */
/*   Updated: 2024/02/28 15:09:43 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include <stdio.h>
#include <math.h>

int32_t	set_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

mlx_texture_t	*get_texture(t_cell_type cell, t_side side, t_attr attributes)
{
	if (cell == MAP_DOOR_CLOSED)
		return (attributes.doors.tex.tex);
	if (side == SIDE_N)
		return (attributes.n.tex);
	else if (side == SIDE_S)
		return (attributes.s.tex);
	else if (side == SIDE_E)
		return (attributes.e.tex);
	return (attributes.w.tex);
}

int32_t	find_wall_color(t_attr atrributes, t_ray *ray, \
						t_vec2i line_points, uint32_t h)
{
	int32_t			color;
	mlx_texture_t	*texture;

	texture = get_texture(ray->hit_cell, ray->hit_side, atrributes);
	wall_texture_position(texture, ray, line_points, h);
	color = pixel_picker(texture, (int)round(ray->texture_point.x), \
							(int)round(ray->texture_point.y));
	return (color);
}

int32_t	find_color(t_rgba rgba)
{
	int32_t	color;

	color = set_color(rgba.r, rgba.g, rgba.b, rgba.a);
	return (color);
}
