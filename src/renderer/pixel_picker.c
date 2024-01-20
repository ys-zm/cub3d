/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_picker.c                                    :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:26:51 by yzaim             #+#    #+#             */
/*   Updated: 2024/01/20 01:16:30 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include <stdio.h>
#include <string.h>

// calculate texture position
void	wall_texture_position(mlx_texture_t *texture, t_ray *ray, t_vec2i line_points, uint32_t h)
{
	static double x_old = 0;
	static double y_old = 0;

	ray->texture_point.x = (int)(ray->wall_x * (double)texture->width);

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

	{
		ray->texture_position = (line_points.x - (double) (h / 2.0) + ray->line_height / 2.0) * ray->step;
		ray->texture_point.y = ((int) ray->texture_position) & (texture->height - 1);

		ray->texture_position += ray->step;
	}
}

uint32_t	pixel_picker(mlx_texture_t *texture, int32_t x, int32_t y)
{
	int32_t	r;
	int32_t	g;
	int32_t	b;
	int32_t	a;
	int32_t	index;

	// printf("x: %u | y: %u\n", x, y);
	index = x * texture->width * BPP + y * BPP;
	// printf("index: %d\n", index);
	r = (uint32_t)texture->pixels[index];
	g = (uint32_t)texture->pixels[index + 1];
	b = (uint32_t)texture->pixels[index + 2];
	a = (uint32_t)texture->pixels[index + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}
