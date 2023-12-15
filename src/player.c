/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   player.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/10 02:25:34 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/15 16:06:23 by joppe         ########   odam.nl         */
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


bool hit_wall(void *p, int32_t x, int32_t y)
{
	t_map *m = (t_map *) p;

	if (m->level[y * m->width + x] == MAP_WALL)
		return (true);
	return (false);
}


void player_raycast(t_player *p)
{
	// iterate over normalized camera space, mapping it to the viewports's width. (-1, 1)
	uint32_t i = 0;
	while (i < p->meta->image->width)
	{

		float cam_x = 2 * i / (double) p->meta->image->width - 1;
		t_vec2f ray_direction = p->direction + p->cam_plane * (t_vec2f) {1.0f, cam_x};
		t_vec2f ray_start = p->position;
		print_vec2f("ray_start", p->position);
		p->rays[i] = raycaster_cast(ray_start, ray_direction, hit_wall);
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
