/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   render_minimap.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 23:14:20 by joppe         #+#    #+#                 */
/*   Updated: 2024/01/06 02:49:44 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "MLX42/MLX42_Int.h"
#include "font/font_comicsans.h"
#include "libft.h"
#include "meta.h"
#include "parser.h"
#include "vector.h"
#include "test_utils.h"
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

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

static void render_info(mlx_image_t *image, const t_player *p)
{
	render_clear_bg(image, 0x666666ff);
	draw_rect(image, 1, 1, image->width - 2, image->height - 2, MINIMAP_COLOR_BACKGROUND);
	const uint32_t text_x = 5;

	const t_font_atlas *font = cube_get_font_atlas(FONT_VT323_19);

	const size_t len = 24;
	char buf[len];
	ft_bzero(buf, len);
	// For some reason addding a space creates some kind of dot in the image.
	snprintf(buf, len, "POS:\t\t\t\tX%.3f\tY%.3f", p->position.x, p->position.y);
	cube_put_string(image, buf, font, text_x, 1);

	snprintf(buf, len, "FPS:\t\t\t\t%u", p->meta->fps);
	// TODO Add the text thing from fdf.
	cube_put_string(image, buf, font, text_x, 1 + font->font_h);
}

void render_minimap(t_minimap *minimap, const t_map *map, const t_player *p)
{
	render_minimap_level(minimap->minimap_image, map, p);
	render_info(minimap->info_image, p);



	static double time_old = -0.4;
	// const char *text = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
	const char *text = "Whereas disregard 123 !@# and contempt for human rights have resulted";

	if (mlx_get_time() - time_old > 0.4)
	{
		render_clear_bg(p->meta->test_image, 0x666666ff);

		cube_put_string(p->meta->test_image, text, cube_get_font_atlas(FONT_DEJAVU_14), 10, 10);
		cube_put_string(p->meta->test_image, text, cube_get_font_atlas(FONT_COMICSANS_14), 10, 80);
		cube_put_string(p->meta->test_image, text, cube_get_font_atlas(FONT_VT323_14), 10, 140);
		cube_put_string(p->meta->test_image, text, cube_get_font_atlas(FONT_VT323_19), 10, 200);
		time_old = mlx_get_time();
	}
}
