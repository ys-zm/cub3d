/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   render.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 23:14:20 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/12 17:08:51 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "meta.h"
#include "vector.h"
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
	const size_t center_x = (image->width / 2) - (CELL_WIDTH * (m->width / 2));
	const size_t center_y = (image->height / 2) - (CELL_HEIGHT * (m->height / 2));
	const size_t x_offset = (cell_x * CELL_WIDTH) + cell_x + center_x;
	const size_t y_offset = (cell_y * CELL_HEIGHT) + cell_y + center_y;
	const t_cell_type cell = (m->level[(cell_y * m->width) + cell_x]);

	draw_square(image, x_offset, y_offset, CELL_WIDTH, CELL_HEIGHT, CELL_COLORS[cell].value);
}

void render_player(mlx_image_t *image, t_player *p)
{
	draw_square(image, p->position[VEC_X] - ((float) PLAYER_WIDTH / 2), p->position[VEC_Y] - ((float) PLAYER_HEIGHT / 2), PLAYER_WIDTH, PLAYER_HEIGHT, COLOR_PLAYER);
	draw_square(image, p->position[VEC_X] - ((float) PLAYER_WIDTH / 2), p->position[VEC_Y] - ((float) PLAYER_HEIGHT / 2), 1, 1, (t_rgba) {0xFF0000fF}.value);

	draw_line(image, vec2f_to_vec2i(p->position),	vec2f_to_vec2i(p->beam), (t_rgba) {0x00FF00FF});
	draw_line(image, vec2f_to_vec2i(p->ray.start), vec2f_to_vec2i(p->ray.end), (t_rgba) {0xDE00EAFF});
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
