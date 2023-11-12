/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   player.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/10 02:25:34 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/12 20:39:11 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "libft.h"
#include "meta.h"
#include "vector.h"
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>


void player_move(t_player *p, t_vec2f transform)
{
	p->position += transform;
	player_look(p, 0.0);
}

void player_look(t_player *p, double angle)
{
	const uint32_t len = 50;

	p->angle = fmod(p->angle + angle, 2 * PI);
	if (p->angle < 0)
		p->angle += 2 * PI;

	p->direction = vec2f_normalize(vec2f_rotate2d(p->angle));
	p->beam = p->position + p->direction * (t_vec2f) {len, len};

	// player_raycast(p);
}

// TODO Abstract out.
// Draws a line until we encounter a wall
void player_raycast(t_player *p)
{
	const t_vec2f	ray_angle = vec2f_rotate2d(p->angle + deg_to_rad(25.0f));
	t_ray* const 	r = &p->ray;
	const size_t	depth = 400;
	t_cell_type		cell;
	size_t			len;

	r->start = p->position;
	r->end = p->position;
	len = 20;
	while (len < depth)
	{
		cell = map_get_cell_type(&p->meta->map, r->end);
		print_cell(cell);
		r->end = r->start + ray_angle * (t_vec2f) {len, len};
		if (cell == MAP_WALL)
		{
			break;
		}
		len++;
	}
}
