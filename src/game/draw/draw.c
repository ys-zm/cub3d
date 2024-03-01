/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                            :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:26:25 by yzaim             #+#    #+#             */
/*   Updated: 2024/03/01 19:08:12 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "meta.h"
#include "draw.h"
#include "vector.h"

void	draw_rect(mlx_image_t *image, t_vec2u pos, t_vec2u size, \
		uint32_t color)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			draw_put_pixel(image, pos.x + x, pos.y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_put_pixel(mlx_image_t *image, uint32_t x, uint32_t y, \
		uint32_t color)
{
	if (x < image->width && y < image->height)
		mlx_put_pixel(image, x, y, color);
}
