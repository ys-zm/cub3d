/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   render_minimap.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 23:14:20 by joppe         #+#    #+#                 */
/*   Updated: 2024/01/04 00:22:17 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "MLX42/MLX42_Int.h"
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
	// TODO memset.
	while (i < size)
	{
		mlx_put_pixel(image, i, 0, c);
		i++;
	}
}

static bool minimap_ray_len(const void *p, uint32_t x, uint32_t y)
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

static void render_minimap_level(mlx_image_t *image, const t_map *map, const t_player *p)
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



#include "../MLX42/src/font/font.h"

static void cube_draw_char(mlx_image_t* image, int32_t texoffset, int32_t imgoffset)
{
	if (texoffset < 0)
		return;

	char* pixelx;
	uint8_t* pixeli;
	for (uint32_t y = 0; y < FONT_HEIGHT; y++)
	{
		pixelx = &font_atlas.pixels[(y * font_atlas.width + texoffset) * BPP];
		pixeli = image->pixels + ((y * image->width + imgoffset) * BPP);
		memcpy(pixeli, pixelx, FONT_WIDTH * BPP);
	}
}

// NOTE: Shamelessly stolen from `mlx_put_string` but modified so we're not constantly allocating a new `mlx_image_t`
mlx_image_t* cube_put_string(mlx_image_t *image, const char* str, int32_t x, int32_t y)
{
	const size_t len = strlen(str);
	int32_t imgoffset = y * image->width + x;
	size_t i = 0;
	while (i < len)
	{
		// get index of font graphics in atlas.
		int32_t  tex_offset = mlx_get_texoffset(str[i]);

		cube_draw_char(image, tex_offset, imgoffset);

		// location where the next char should be drawn in the image.
		imgoffset += FONT_WIDTH;
		i++;
	}

	i = 0;
	while (i < image->width * image->height)
	{
		uint8_t *pixelstart = &image->pixels[i * BPP];
		if (*pixelstart == 0x0)
			mlx_draw_pixel(pixelstart, MINIMAP_COLOR_BACKGROUND);
		i++;
	}

	return image;
}

static void render_info(mlx_image_t *image, const t_player *p)
{
	render_clear_bg(image, 0x666666ff);
	draw_rect(image, 1, 1, image->width - 2, image->height - 2, MINIMAP_COLOR_BACKGROUND);

	cube_put_string(image, "poep", 10, 10);

}

void render_minimap(t_minimap *minimap, const t_map *map, const t_player *p)
{
	render_minimap_level(minimap->minimap_image, map, p);
	render_info(minimap->info_image, p);
}
