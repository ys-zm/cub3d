/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   player.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/10 02:25:34 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/14 20:13:55 by jboeve        ########   odam.nl         */
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
#include <stdlib.h>


void player_move(t_player *p, t_vec2f transform)
{
	p->position += transform;
	player_look(p, 0.0);
}

void player_look(t_player *p, double angle)
{
	const uint32_t len = 50;

	p->angle_rad = fmod(p->angle_rad + angle, 2 * PI);
	if (p->angle_rad < 0)
		p->angle_rad += 2 * PI;

	p->direction = vec2f_normalize(vec2f_rotate2d(p->angle_rad));
	p->beam = p->position + p->direction * (t_vec2f) {len, len};

	player_raycast(p);
}

void player_raycast(t_player *p)
{
	// iterate over normalized camera space, mapping it to the viewports's width. (-1, 1)
	uint32_t i = 0;
	while (i < p->meta->image->width)
	{
		t_ray *r = &p->rays[i];
		// TODO Maybe a double.
		float cam_x = 2 * i / (double) p->meta->image->width - 1;
		r->direction = p->direction + p->cam_plane * (t_vec2f) {1.0f, cam_x};

		r->delta_distance[VEC_X] = (r->direction[VEC_X] == 0) ? 1e30 : fabs(1 / r->direction[VEC_X]);
		r->delta_distance[VEC_Y] = (r->direction[VEC_Y] == 0) ? 1e30 : fabs(1 / r->direction[VEC_Y]);

		r->map_pos = vec2f_to_vec2i(p->position) / CELL_SIZE;

		if (r->direction[VEC_X] < 0)
		{
			r->step[VEC_X] = -1;
			r->side_distance[VEC_X] = (p->position[VEC_X] - r->map_pos[VEC_X]) * r->delta_distance[VEC_X];
		}
		else
		{
			r->step[VEC_X] = 1;
			r->side_distance[VEC_X] = (r->map_pos[VEC_X] + 1.0f - p->position[VEC_X]) * r->delta_distance[VEC_X];
		}
		if (r->direction[VEC_Y] < 0)
		{
			r->step[VEC_Y] = -1;
			r->side_distance[VEC_Y] = (p->position[VEC_Y] - r->map_pos[VEC_Y]) * r->delta_distance[VEC_Y];
		}
		else
		{
			r->step[VEC_Y] = 1;
			r->side_distance[VEC_Y] = (r->map_pos[VEC_Y] + 1.0f - p->position[VEC_Y]) * r->delta_distance[VEC_Y];
		}

		r->hit = false;
		while (!r->hit)
		{
			if (r->side_distance[VEC_X] < r->side_distance[VEC_Y])	
			{
				r->side_distance[VEC_X] += r->delta_distance[VEC_X];
				r->map_pos[VEC_X] += r->step[VEC_X];
				r->hit_side = HIT_NS;
			}
			else
			{
				r->side_distance[VEC_Y] += r->delta_distance[VEC_Y];
				r->map_pos[VEC_Y] += r->step[VEC_Y];
				r->hit_side = HIT_EW;
			}
			if (p->meta->map.level[find_index(p->meta, r->map_pos[VEC_X], r->map_pos[VEC_Y])] != MAP_SPACE)
				r->hit = true;
		}

		if(r->hit_side == HIT_EW)
		{
			r->perp_wall_distance = (r->side_distance[VEC_Y] - r->delta_distance[VEC_Y]);
		}
		else
			r->perp_wall_distance = (r->side_distance[VEC_X] - r->delta_distance[VEC_X]);


		// r->len = (int)(p->meta->image->height / r->perp_wall_distance);
		// TODO LEFT OFF HERE
		printf("ray len %d\n", r->perp_wall_distance);

		i++;
	}
}


static t_ray raycast(t_map *map, t_vec2f start, t_vec2f angle, size_t depth)
{
	t_cell_type	cell;
	size_t		len;
	t_ray		r;

	r.direction = start;
	r.end = start;
	len = 0;
	while (len < depth)
	{
		cell = map_get_cell_type(map, r.end);
		r.end = r.direction + angle * (t_vec2f) {len, len};
		if (cell == MAP_WALL)
			break;
		len++;
	}
	return r;
}

// TODO Abstract out.
// Draws a line until we encounter a wall
void player_raycast1(t_player *p)
{
	const size_t depth = 500;
	t_vec2f	dir;
	size_t	i;

	i = 0;
	while (i < PLAYER_RAY_COUNT)
	{
		dir = vec2f_normalize(vec2f_rotate2d(p->angle_rad + deg_to_rad(i) - (deg_to_rad(PLAYER_RAY_COUNT) / 2)));
		p->rays[i] = raycast(&p->meta->map, p->position, dir, depth);
		i++;	
	}
}
