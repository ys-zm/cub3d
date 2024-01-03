/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   render_minimap.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 23:14:20 by joppe         #+#    #+#                 */
/*   Updated: 2024/01/03 22:07:03 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "meta.h"
#include "parser.h"
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

void draw_cell(mlx_image_t *image, t_cell_type cell, const uint32_t x, const uint32_t y)
{
	draw_rect(image, x, y, MINIMAP_CELL_SIZE, MINIMAP_CELL_SIZE, CELL_COLORS[cell].value);
}


void render_minimap(mlx_image_t *image, t_map *map, const t_player *p)
{
	render_clear_bg(image, MINIMAP_COLOR_BACKGROUND);
	t_vec2i start = {(image->width / 2), (image->height / 2)};

	uint32_t center_x = start.x - (p->position.x * MINIMAP_CELL_SIZE);
	uint32_t center_y = start.y - (p->position.y * MINIMAP_CELL_SIZE);
	size_t x = 0;
	while (x < map->width)
	{
		size_t y = 0;
		while (y < map->height)
		{
			int32_t cell_x = center_x + (x * MINIMAP_CELL_SIZE);
			int32_t cell_y = center_y + (y * MINIMAP_CELL_SIZE);
			if (cell_x + MINIMAP_CELL_SIZE >= 0 && cell_x < (int32_t) image->width && cell_y + MINIMAP_CELL_SIZE >= 0 && cell_y < (int32_t) image->height)
				draw_cell(image, map->level[(y * map->width) + x], cell_x, cell_y);
			y++;
		}
		x++;
	}


	t_ray r = raycaster_cast(p->position, p->direction, minimap_ray_len, map);

	draw_rect(image, start.x - (MINIMAP_PLAYER_SIZE / 2) , start.y - (MINIMAP_PLAYER_SIZE / 2), MINIMAP_PLAYER_SIZE, MINIMAP_PLAYER_SIZE, MINIMAP_COLOR_PLAYER);

	t_vec2i end = vec2d_to_vec2i(vec2d_add((t_vec2d) {start.x, start.y}, vec2d_scalar_product(p->direction, (r.length) * MINIMAP_CELL_SIZE)));
	draw_line(image, start, end, (t_rgba) {0xFFFF00FF});
}
