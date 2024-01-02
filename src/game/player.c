/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   player.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/10 02:25:34 by joppe         #+#    #+#                 */
/*   Updated: 2024/01/02 23:09:34 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "libft.h"
#include "test_utils.h"
#include "meta.h"
#include "vector.h"
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool bound_check(void *param, uint32_t x, uint32_t y)
{
	t_meta *const meta = (t_meta *) param;
	if (x < meta->map.width && y < meta->map.height)
		return (meta->map.level[(y * meta->map.width) + x] == MAP_WALL);
	else
	{
		UNIMPLEMENTED("Map out of bounds.");
	}
}

void player_move(t_player *p, t_vec2d transform)
{
	t_vec2d	new_position;

	new_position.x = (p->position.x + (transform.x));
	new_position.y = (p->position.y + (transform.y));

	t_ray r = raycaster_cast(p->meta, p->position, vec2d_normalize(transform), bound_check);
	// print_ray("bound_ray", &r);

	if (r.length > .5)
	{
		p->position.x += transform.x;
		p->position.y += transform.y;
	}
	player_raycast(p);
}

// negative rotation parameter turns left vs positive rotation parameter turns right
void player_turn(t_player *p, float radiant)
{
	p->direction = vec2d_rotate(p->direction, radiant);
	p->cam_plane = vec2d_rotate(p->cam_plane, radiant);
	player_raycast(p);
}

void player_raycast(t_player *p)
{
	uint32_t w = p->meta->image->width;
	uint32_t col;
	t_vec2d	ray_start;
	double	camera_x;

	// TODO Just create the player.plane here instead of saving it.
	col = 0;
	while(col < w)
	{
		camera_x = (2 * col / ((double) w) - 1);
		ray_start = vec2d_add(p->direction, vec2d_scalar_product(p->cam_plane, camera_x));
		p->rays[col] = raycaster_cast(p->meta, p->position, ray_start, bound_check);
		col++;
	}
}
