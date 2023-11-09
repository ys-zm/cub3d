/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   render.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 23:14:20 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/09 01:13:25 by joppe         ########   odam.nl         */
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
	[MAP_WALL]	= {0x004ebaff},
	[MAP_SPACE]	= {0x696969ff},
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


void draw_cell(t_meta *meta, t_cell_type cell, uint32_t cell_x, uint32_t cell_y)
{
	const size_t center_x = (meta->image->width / 2) - (CELL_WIDTH * (MAP_WIDTH / 2));
	const size_t center_y = (meta->image->height / 2) - (CELL_HEIGHT * (MAP_HEIGHT / 2));
	const size_t x_offset = (cell_x * CELL_WIDTH) + cell_x + center_x;
	const size_t y_offset = (cell_y * CELL_HEIGHT) + cell_y + center_y;

	size_t x;
	size_t y;


	y = 0;
	while (y < CELL_HEIGHT)
	{
		x = 0;
		while (x < CELL_WIDTH)
		{
			cube_put_pixel(meta->image, x + x_offset, y + y_offset, CELL_COLORS[cell].value);
			x++;
		}
		y++;
	}
}


void render_map_grid(t_meta *meta)
{
	size_t cell_y;
	size_t cell_x;

	cell_y = 0;
	while (cell_y < MAP_HEIGHT)
	{
		cell_x = 0;
		while (cell_x < MAP_WIDTH)
		{
			draw_cell(meta, MAP[(cell_y * MAP_WIDTH) + cell_x], cell_x, cell_y);
			cell_x++;
		}
		cell_y++;
	}
}

void render_clear_bg(mlx_image_t *image)
{
	const uint32_t	size = image->width * image->height;
	size_t			i;

	i = 0;
	while (i < size)
	{
		mlx_put_pixel(image, i, 0, COLOR_BACKGROUND);
		i++;
	}
}
