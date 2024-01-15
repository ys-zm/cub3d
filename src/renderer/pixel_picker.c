/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:26:51 by yzaim             #+#    #+#             */
/*   Updated: 2024/01/08 15:29:57 by yzaim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include <stdio.h>
#include <string.h>

// calculate texture position
void	wall_texture_position(t_tex texture, t_ray *ray, t_vec2d line_points, uint32_t h)
{
	// printf("wall x: %f\n", ray->wall_x);
	ray->texture.x = (int)(ray->wall_x * (double)texture.tex->width);
	if ((ray->hit_side == SIDE_N || ray->hit_side == SIDE_S) && ray->direction.x > 0)
	{
		ray->texture.x = texture.tex->width - ray->texture.x - 1;
	}
	if ((ray->hit_side == SIDE_E || ray->hit_side == SIDE_W) && ray->direction.y < 0)
	{
		ray->texture.x = texture.tex->width - ray->texture.x - 1;
	}
	ray->step = 1.0 * texture.tex->height / ray->line_height;
	// printf("step: %f\n", ray->step);
	// x is draw start and y is draw end
	ray->texture_position = (line_points.x + (ray->line_height - h )/ 2) * ray->step;
}

uint32_t	pixel_picker(t_tex texture, uint32_t x, uint32_t y)
{
	uint32_t color = 0;
	int32_t	index;

	// printf("x: %u | y: %u\n", x, y);
	index = (y % texture.tex->width) * texture.tex->width * 4 +(x % texture.tex->width) * 4;
	// printf("index: %d\n", index);
	color |= (uint32_t)texture.tex->pixels[index] << 24;
	color |= (uint32_t)texture.tex->pixels[index + 1] << 16;
	color |= (uint32_t)texture.tex->pixels[index + 2] << 8;
	color |= (uint32_t)texture.tex->pixels[index + 3];
	return (color);
}