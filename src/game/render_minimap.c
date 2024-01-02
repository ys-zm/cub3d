/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   render_minimap.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 23:14:20 by joppe         #+#    #+#                 */
/*   Updated: 2024/01/03 00:34:31 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "vector.h"
#include "test_utils.h"
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

void render_clear_bg(mlx_image_t *image, uint32_t c)
{
	const uint32_t	size = image->width * image->height;
	size_t			i;

	i = 0;
	while (i < size)
	{
		mlx_put_pixel(image, i, 0, c);
		i++;
	}
}

static bool minimap_ray_len(void *p, uint32_t x, uint32_t y)
{
	t_map *const map = (t_map *) p;
	if (x < map->width && y < map->height)
		return (map->level[(y * map->width) + x] == MAP_WALL);
	else
	{
		UNIMPLEMENTED("also map out of bounds.");
	}
}

void render_minimap(mlx_image_t *image, t_map *map, const t_player *p)
{
	const uint32_t size = 24;
	// const double len = 50.0;

	render_clear_bg(image, COLOR_BACKGROUND);

	t_ray dir = raycaster_cast(p->position, p->direction, minimap_ray_len, map);

	t_vec2i start = {(image->width / 2), (image->height / 2)};

	draw_rect(image, start.x - (size / 2) , start.y - (size / 2), size, size, COLOR_PLAYER);
	t_vec2i end = vec2d_to_vec2i(vec2d_add((t_vec2d) {start.x, start.y}, vec2d_scalar_product(p->direction, (dir.length) * CELL_SIZE)));

	draw_line(image, start, end, (t_rgba) {0xFFFF00FF});
}
