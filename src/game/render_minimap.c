/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                  :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:27:53 by yzaim             #+#    #+#             */
/*   Updated: 2024/02/17 00:34:01 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "libft.h"
#include "meta.h"
#include "parser.h"
#include "vector.h"
#include "test_utils.h"
#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

static const t_rgba CELL_COLORS[] = {
	[MAP_EMPTY]			= {MINIMAP_COLOR_BACKGROUND},
	[MAP_WALL] 			= {0x323232ff},
	[MAP_SPACE]			= {0xcdcdcdff},
	[MAP_DOOR_OPEN]		= {0xddddddff},
	[MAP_DOOR_CLOSED]	= {0x148f91ff},
};


static void render_clear_bg(mlx_image_t *image, uint32_t c)
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

static t_cell_type minimap_ray_len(const void *p, uint32_t x, uint32_t y)
{
	t_map *const map = (t_map *) p;

	const t_cell_type cur_cell = map->level[(y * map->width) + x];

	if (x < map->width && y < map->height)
	{
		if (cur_cell == MAP_WALL || cur_cell == MAP_DOOR_CLOSED)
			return (cur_cell);
		else
		 	return (0);
	}
	else
		UNIMPLEMENTED("Map out of bounds.");
}

void draw_cell(mlx_image_t *image, t_cell_type cell, const uint32_t x, const uint32_t y)
{
	draw_rect(image, x, y, MINIMAP_CELL_SIZE, MINIMAP_CELL_SIZE, CELL_COLORS[cell].value);
}

static void render_border(mlx_image_t *image, uint32_t c)
{
	uint32_t i = 0;
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

static void render_minimap_level(mlx_image_t *image, const t_map *map, const t_player *p)
{
	render_clear_bg(image, MINIMAP_COLOR_BACKGROUND);
	const t_vec2i image_center = {(image->width / 2), (image->height / 2)};
	const uint32_t pp_center_x = image_center.x - (p->position.x * MINIMAP_CELL_SIZE);
	const uint32_t pp_center_y = image_center.y - (p->position.y * MINIMAP_CELL_SIZE);
	size_t x;

	x = 0;
	while (x < map->width)
	{
		size_t y = 0;
		while (y < map->height)
		{
			int32_t cell_x = pp_center_x + (x * MINIMAP_CELL_SIZE);
			int32_t cell_y = pp_center_y + (y * MINIMAP_CELL_SIZE);
			if (cell_x + MINIMAP_CELL_SIZE >= 0 && cell_x < (int32_t) image->width && cell_y + MINIMAP_CELL_SIZE >= 0 && cell_y < (int32_t) image->height)
				draw_cell(image, map->level[(y * map->width) + x], cell_x, cell_y);
			y++;
		}
		x++;
	}


	for (size_t i = 0; i < WINDOW_WIDTH; i++)
	{
		const t_ray *r = &p->hrays[i];


		t_vec2i end = vec2d_to_vec2i(vec2d_add((t_vec2d) {image_center.x, image_center.y}, vec2d_scalar_product(r->direction, (r->length) * MINIMAP_CELL_SIZE)));
		draw_line(image, image_center, end, (t_rgba) {0x999999FF});
	
	}
	draw_rect(image, image_center.x - (MINIMAP_PLAYER_SIZE / 2) , image_center.y - (MINIMAP_PLAYER_SIZE / 2), MINIMAP_PLAYER_SIZE, MINIMAP_PLAYER_SIZE, MINIMAP_COLOR_PLAYER);
	
	render_border(image, MINIMAP_COLOR_BORDER);
}

static void render_info(t_minimap *minimap, const t_player *p)
{
	t_font_atlas const	*font = cube_get_font_atlas(FONT_COMICSANS_13);
	const size_t 		len = 32;
	char				buf[len];

	ft_bzero(buf, len);
	snprintf(buf, len, "POS:   X%.3f\tY%.3f", p->position.x, p->position.y);
	minimap->ppos_image = cube_put_string(minimap->ppos_image, buf, font);
	snprintf(buf, len, "FPS:   %u", p->meta->fps);
	minimap->fps_image = cube_put_string(minimap->fps_image, buf, font);


	minimap->hud_image = cube_put_string(minimap->hud_image, "Press [F] to interact", font);



	render_clear_bg(minimap->info_image, MINIMAP_COLOR_BORDER);
	draw_rect(minimap->info_image, 1, 1, minimap->info_image->width - 2, minimap->info_image->height - 2, MINIMAP_COLOR_BACKGROUND);
}

void render_minimap(t_minimap *minimap, const t_map *map, const t_player *p)
{
	render_minimap_level(minimap->minimap_image, map, p);
	render_info(minimap, p);
}
