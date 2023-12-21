/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   render.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 23:14:20 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/21 00:10:30 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


const t_rgba CELL_COLORS[] = {
	[MAP_EMPTY]	= {0xff00aaff},
	[MAP_WALL]	= {0x004ebaff},
	[MAP_SPACE]	= {0x696969ff},
};

void draw_cell(mlx_image_t *image, t_map *m, uint32_t cell_x, uint32_t cell_y)
{
	const size_t x_offset = (cell_x * CELL_WIDTH);
	const size_t y_offset = (cell_y * CELL_HEIGHT);

	const t_cell_type cell = (m->level[(cell_y * m->width) + cell_x]);

	draw_rect(image, x_offset, y_offset, CELL_WIDTH, CELL_HEIGHT, CELL_COLORS[cell].value);
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

void render_player_viewport(mlx_image_t *image, t_player *p)
{

}

void render_minimap(mlx_image_t *image, t_map *m)
{
	size_t cell_y;
	size_t cell_x;

	cell_y = 0;
	while (cell_y < m->height)
	{
		cell_x = 0;
		while (cell_x < m->width)
		{
			draw_cell(image, m, cell_x, cell_y);
			cell_x++;
		}
		cell_y++;
	}
}
