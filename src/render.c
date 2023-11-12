/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   render.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 23:14:20 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/12 19:52:23 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "meta.h"
#include "vector.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


#define MAP_OFFSET_X 256
#define MAP_OFFSET_Y 104

const t_vec2i DRAW_OFFSET = {
	MAP_OFFSET_X, MAP_OFFSET_Y
};

const t_rgba CELL_COLORS[] = {
	[MAP_EMPTY]	= {0xff00aaff},
	[MAP_WALL]	= {0x004ebaff},
	[MAP_SPACE]	= {0x696969ff},
};



void draw_cell(mlx_image_t *image, t_map *m, uint32_t cell_x, uint32_t cell_y)
{
	const size_t x_offset = (cell_x * CELL_WIDTH) + cell_x + DRAW_OFFSET[VEC_X];
	const size_t y_offset = (cell_y * CELL_HEIGHT) + cell_y + DRAW_OFFSET[VEC_Y];
	const t_cell_type cell = (m->level[(cell_y * m->width) + cell_x]);

	draw_square(image, x_offset, y_offset, CELL_WIDTH, CELL_HEIGHT, CELL_COLORS[cell].value);
}

// The player is essentially just a single point/pixel, around which we draw a square with the "player point" in its center.
void render_player(mlx_image_t *image, t_player *p)
{
	t_vec2i draw_pos = vec2f_to_vec2i(p->position) + DRAW_OFFSET;
	draw_pos[VEC_X] -= ((float) PLAYER_WIDTH / 2);
	draw_pos[VEC_Y] -= ((float) PLAYER_HEIGHT / 2);

	// Draw the player square.
	draw_square(image,	draw_pos[VEC_X], draw_pos[VEC_Y],
						PLAYER_WIDTH, PLAYER_HEIGHT, COLOR_PLAYER);

	draw_line(image,	vec2f_to_vec2i(p->position) + DRAW_OFFSET,	
						vec2f_to_vec2i(p->beam) + DRAW_OFFSET,
						(t_rgba) {0x00FF00FF});
	draw_line(image, 	vec2f_to_vec2i(p->ray.start) + DRAW_OFFSET,
						vec2f_to_vec2i(p->ray.end) + DRAW_OFFSET,
						(t_rgba) {0xDE00EAFF});
}

void render_map_grid(mlx_image_t *image, t_map *m)
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
