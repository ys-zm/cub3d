/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   render_minimap_utils.c                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/03/01 19:29:06 by joppe         #+#    #+#                 */
/*   Updated: 2024/05/29 12:20:49 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "vector.h"
#include <stdint.h>

t_rgba	get_cell_color(t_cell_type cell)
{
	const t_rgba	cell_colors[] = {
	[MAP_EMPTY] = {MINIMAP_COLOR_BACKGROUND},
	[MAP_WALL] = {0x323232ff},
	[MAP_SPACE] = {0xcdcdcdff},
	[MAP_DOOR_OPEN] = {0xddddddff},
	[MAP_DOOR_CLOSED] = {0x148f91ff},
	};

	return (cell_colors[cell]);
}

void	render_clear_bg(mlx_image_t *image, uint32_t c)
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

t_cell_type	minimap_ray_len(const void *p, uint32_t x, uint32_t y)
{
	t_map *const		map = (t_map *) p;
	const t_cell_type	cur_cell = map->level[(y * map->width) + x];

	if (x < map->width && y < map->height)
	{
		if (cur_cell == MAP_WALL || cur_cell == MAP_DOOR_CLOSED)
			return (cur_cell);
		else
			return (0);
	}
	return (0);
}

void	draw_cell(mlx_image_t *image, t_cell_type cell, t_vec2u start, uint32_t size)
{
	draw_rect(image, start, (t_vec2u){size, size}, get_cell_color(cell).value);
}

void	render_border(mlx_image_t *image, uint32_t c)
{
	uint32_t	i;

	i = 0;
	while (i < image->height)
	{
		draw_put_pixel(image, 0, i, c);
		draw_put_pixel(image, image->width - 1, i, c);
		i++;
	}
	i = 0;
	while (i < image->width)
	{
		draw_put_pixel(image, i, 0, c);
		i++;
	}
}
