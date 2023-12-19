/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   player.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/10 02:25:34 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/19 23:40:47 by joppe         ########   odam.nl         */
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
	const float len = 1.4f;

	p->angle_rad = fmod(p->angle_rad + angle, 2 * PI);
	if (p->angle_rad < 0)
		p->angle_rad += 2 * PI;

	p->direction = vec2f_normalize(vec2f_rotate2d(p->angle_rad));
	p->beam = p->position + p->direction * (t_vec2f) {len, len};

	p->cam_plane = (t_vec2f) {0.0f, 0.66f};



	// const float rot_step = deg_to_rad(p->angle_rad);
	// double oldPlaneX = p->cam_plane[VEC_X];
	// p->cam_plane[VEC_X] = p->cam_plane[VEC_X]	* cos(rot_step) - p->cam_plane[VEC_Y] * sin(rot_step);
	// p->cam_plane[VEC_Y] = oldPlaneX				* sin(rot_step) + p->cam_plane[VEC_Y] * cos(rot_step);

	player_raycast(p);
}


bool hit_wall(void *p, int32_t x, int32_t y)
{
	t_map *m = (t_map *) p;

	const size_t index = y * m->width + x;
	if (index > m->width * m->height)
		printf("MAP OUT OF BOIUNDS\n");
	else if (m->level[index] == MAP_WALL)
		return (true);
	return (false);
}


void player_raycast(t_player *p)
{
	uint32_t i = 0;
	while (i < p->meta->image->width)
	{
		float camera_x = 2 * i / (double) p->meta->image->width - 1;
		t_vec2f ray_direction = p->direction;
		t_vec2f ray_start = (p->position + p->cam_plane);

		p->rays[i] = raycaster_cast(p->meta, ray_start, ray_direction, hit_wall);
		i++;
	}
}
