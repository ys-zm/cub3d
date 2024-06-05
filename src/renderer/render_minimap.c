/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_minimap.c                                  :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:27:53 by yzaim         #+#    #+#                 */
/*   Updated: 2024/06/05 13:29:52 by yesimzaim     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "meta.h"
#include "vector.h"
#include "render_minimap.h"
#include <stdint.h>

#define BUF_LEN 32

// Loops over the map and draws a colored tile for each cell 
static void	draw_tiles(mlx_image_t *image, const t_vec2i image_center, const t_player *p, const t_map *map)
{
	const uint32_t	pp_center_x = image_center.x - (uint32_t)(p->position.x * p->meta->minimap.tile_size);
	const uint32_t	pp_center_y = image_center.y - (uint32_t)(p->position.y * p->meta->minimap.tile_size);

	printf("PPcenter: (%d, %d)\n", pp_center_x, pp_center_y);
	printf("ImageCenter: (%d, %d) | Player Pos: (%f, %f)\n", image_center.x, image_center.y, p->position.x, p->position.y);
	size_t			loop[2];
	int32_t			cell_pos[2];
	const size_t	size = p->meta->minimap.tile_size;


	loop[0] = 0;
	while (loop[0] < map->width)
	{
		loop[1] = 0;
		while (loop[1] < map->height)
		{
			cell_pos[0] = pp_center_x + (loop[0] * size);
			cell_pos[1] = pp_center_y + (loop[1] * size);
			if (cell_pos[0] + (int32_t) p->meta->minimap.tile_size >= 0 && cell_pos[0] < (int32_t) image->width && cell_pos[1] + (int32_t) size >= 0 && cell_pos[1] < (int32_t) image->height)
			{
				draw_cell(image, map->level[(loop[1] * map->width) + loop[0]], (t_vec2u){cell_pos[0], cell_pos[1]}, size);
			}
			loop[1]++;
		}
		loop[0]++;
	}
}

static void	render_minimap_level(mlx_image_t *image, const t_map *map, const t_player *p)
{
	const t_vec2i	image_center = {(image->width / 2), (image->height / 2)};
	size_t			i;
	t_ray const		*r;
	const t_vec2u	pos = {
		image_center.x - (MINIMAP_PLAYER_SIZE / 2),
		image_center.y - (MINIMAP_PLAYER_SIZE / 2)
	};
	const size_t	size = p->meta->minimap.tile_size;
	render_clear_bg(image, MINIMAP_COLOR_BACKGROUND);
	draw_tiles(image, image_center, p, map);
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		r = &p->hrays[i];
		draw_line(image, image_center, vec2d_to_vec2i(vec2d_add((t_vec2d){image_center.x, image_center.y}, vec2d_scalar_product(r->direction, r->length * size))), (t_rgba){0x999999FF});
		// if ( i == WINDOW_WIDTH / 2)
		// {
		// 	// Debugging output
  //       	printf("Ray %zu: Start (%d, %d) Direction (%.3f, %.3f) Length %.3f Size %zu\n",
  //              i, image_center.x, image_center.y, r->direction.x, r->direction.y, r->length, size);
		//
		// }
		i++;
	}
	draw_rect(image, pos, (t_vec2u){MINIMAP_PLAYER_SIZE, MINIMAP_PLAYER_SIZE}, MINIMAP_COLOR_PLAYER);
	render_border(image, MINIMAP_COLOR_BORDER);
}

static void	render_info(t_minimap *minimap, const t_player *p)
{
	t_font_atlas const	*font = cube_get_font_atlas(FONT_COMICSANS_13);
	char				buf[BUF_LEN];
	const t_vec2u		size = {
		minimap->info_image->width - 2,
		minimap->info_image->height - 2
	};

	ft_bzero(buf, BUF_LEN);
	snprintf(buf, BUF_LEN, "POS:   X%.3f\tY%.3f", p->position.x, p->position.y);
	minimap->ppos_image = cube_put_string(minimap->ppos_image, buf, font);
	snprintf(buf, BUF_LEN, "FPS:   %u", p->meta->fps);
	minimap->fps_image = cube_put_string(minimap->fps_image, buf, font);
	render_clear_bg(minimap->info_image, MINIMAP_COLOR_BORDER);
	draw_rect(minimap->info_image, (t_vec2u){1, 1}, size, MINIMAP_COLOR_BACKGROUND);
}

void	render_minimap(t_minimap *minimap, const t_map *map, const t_player *p)
{
	render_minimap_level(minimap->minimap_image, map, p);
	render_info(minimap, p);
}
