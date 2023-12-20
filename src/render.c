/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   render.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 23:14:20 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/20 13:06:22 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	const size_t x_offset = (cell_x * CELL_WIDTH);
	const size_t y_offset = (cell_y * CELL_HEIGHT);

	const t_cell_type cell = (m->level[(cell_y * m->width) + cell_x]);

	draw_rect(image, x_offset, y_offset, CELL_WIDTH, CELL_HEIGHT, CELL_COLORS[cell].value);
}

// The player is essentially just a single point/pixel, around which we draw a square with the "player point" in its center.
void render_player(mlx_image_t *image, t_player *p)
{
	t_vec2i draw_pos = vec2f_to_vec2i(p->position * (t_vec2f) {CELL_SIZE, CELL_SIZE});

	draw_pos[VEC_X] -= ((float) PLAYER_WIDTH / 2);
	draw_pos[VEC_Y] -= ((float) PLAYER_HEIGHT / 2);

	// Draw the player square.
	draw_rect(image,	draw_pos[VEC_X], draw_pos[VEC_Y],
						PLAYER_WIDTH, PLAYER_HEIGHT, COLOR_PLAYER);


	// Draw cam plane.
	draw_line(image, vec2f_to_vec2i((p->position - p->cam_plane) * CELL_SIZE), vec2f_to_vec2i((p->position + p->cam_plane) * CELL_SIZE), (t_rgba) {0xFFF000FF});


	// Draw the player look direction.
	draw_line(image,	vec2f_to_vec2i(p->position * CELL_SIZE),	
						vec2f_to_vec2i(p->beam * CELL_SIZE),
						(t_rgba) {0x00FF00FF});

}

void render_player_viewport(mlx_image_t *image, t_player *p)
{

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
