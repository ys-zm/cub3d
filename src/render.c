/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   render.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 23:14:20 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/08 23:53:10 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "meta.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>


#define MAP_WIDTH 8
#define MAP_HEIGHT 8

#define CELL_WIDTH 64
#define CELL_HEIGHT 64


const t_rgba CELL_COLORS[] = {
	[MAP_EMPTY]	= {0xff00aaff},
	[MAP_WALL]	= {0x00ffaaff},
	[MAP_SPACE]	= {0x00aaffff},
};


const t_cell_type MAP[] = {
	MAP_WALL, MAP_WALL, MAP_WALL, MAP_WALL, MAP_WALL, MAP_WALL, MAP_WALL, MAP_WALL,
	MAP_WALL, MAP_SPACE, MAP_SPACE, MAP_SPACE, MAP_SPACE, MAP_WALL, MAP_SPACE, MAP_WALL,
	MAP_WALL, MAP_SPACE, MAP_SPACE, MAP_SPACE, MAP_SPACE, MAP_SPACE, MAP_SPACE, MAP_WALL,
	MAP_WALL, MAP_SPACE, MAP_SPACE, MAP_SPACE, MAP_SPACE, MAP_WALL, MAP_WALL, MAP_WALL,
	MAP_WALL, MAP_SPACE, MAP_SPACE, MAP_WALL, MAP_SPACE, MAP_SPACE, MAP_SPACE, MAP_WALL,
	MAP_WALL, MAP_SPACE, MAP_SPACE, MAP_WALL, MAP_SPACE, MAP_SPACE, MAP_SPACE, MAP_WALL,
	MAP_WALL, MAP_SPACE, MAP_SPACE, MAP_WALL, MAP_SPACE, MAP_SPACE, MAP_SPACE, MAP_WALL,
	MAP_WALL, MAP_WALL, MAP_WALL, MAP_WALL, MAP_WALL, MAP_WALL, MAP_WALL, MAP_WALL,
};


void draw_cell(t_meta *meta, t_cell_type cell, uint32_t x, uint32_t y)
{
	size_t x_start;
	size_t y_start;

	const size_t x_offset = x * CELL_WIDTH;
	const size_t y_offset = y * CELL_HEIGHT;

	y_start = 0;
	while (y_start < CELL_HEIGHT)
	{
		x_start = 0;
		while (x_start < CELL_WIDTH)
		{
			mlx_put_pixel(meta->image, x_offset + x_start, y_offset + y_start, CELL_COLORS[cell].value);
			x_start++;
		}
		y_start++;
	}
}


void render_map_grid(t_meta *meta)
{
	size_t y;
	size_t x;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			draw_cell(meta, MAP[(y * MAP_WIDTH) + x], x, y);
			x++;
		}
		y++;
	}
}

void render_clear_bg(mlx_image_t *image)
{
	const uint32_t	size = image->width * image->height;
	size_t			i;

	// memset(img->pixels, 255, sizeof(int32_t) * img->width * img->height);

	i = 0;
	while (i < size)
	{
		mlx_put_pixel(image, i, 0, COLOR_BACKGROUND);
		i++;
	}
}
