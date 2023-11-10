/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   player.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/10 02:25:34 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/10 21:23:58 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "libft.h"
#include "meta.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>

t_vec2i map_get_cell(mlx_image_t *image, t_vec2i pos)
{
	const size_t center_x = (image->width / 2) - (CELL_WIDTH * (MAP_WIDTH / 2));
	const size_t center_y = (image->height / 2) - (CELL_HEIGHT * (MAP_HEIGHT / 2));
	const size_t x_offset = (cell_x * CELL_WIDTH) + cell_x + center_x;
	const size_t y_offset = (cell_y * CELL_HEIGHT) + cell_y + center_y;

	const size_t x = (x_offset - center_x / 65)

	return (t_vec2i) {x_offset, y_offset};
}


void player_move(t_player *p, t_vec2f transform)
{
	p->position += p->direction * transform;

	p->map_position = map_get_cell(p->meta->image, vec2f_to_vec2i(p->position));
	print_vec2i("map pos", p->map_position);

	player_look(p, 0.0);
}

void player_look(t_player *p, double angle)
{
	const uint32_t len = 50;

	p->angle += angle;
	if (p->angle > 2 * PI)
		p->angle -= 2 * PI;
	else if (p->angle < 0)
		p->angle += 2 * PI;

	p->direction = vec2f_normalize(vec2f_rotate2d(p->angle));
	p->beam = p->position + p->direction * (t_vec2f) {len, len};


	// print_vec2f("direction", p->direction);
	// print_vec2f("beam", p->beam);
	// print_vec2f("pos", p->position);
	player_raycast(p, NULL);
}

// TODO Abstract out.
// calculates the length of the p->beam.
void player_raycast(t_player *p, t_cell_type *map)
{
	UNUSED(map);
	t_ray* const r = &p->ray;
	const t_vec2f ray_angle = vec2f_rotate2d(p->angle + deg_to_rad(20.0f));
	const size_t depth = 100;
	size_t len;


	r->start = p->position;
	len = 0;
	while (len < depth)
	{
		r->end = r->start + ray_angle * (t_vec2f) {len, len};
		
		len++;
	}
}
