/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:27:23 by yzaim         #+#    #+#                 */
/*   Updated: 2024/01/24 14:06:15 by yzaim         ########   odam.nl         */
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

	// TODO Fix.
	t_ray r = raycaster_cast(p->position, vec2d_normalize(transform), bound_check, p->meta);
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
	uint32_t	w = p->meta->image->width;
	uint32_t	h = p->meta->image->height;
	uint32_t	col;
	uint32_t	row;
	t_vec2d		ray_start;
	double		camera_x;

	row = 0;
	while (row < h)
	{
		p->vrays[row] = floorcaster(p->position, p->direction, p->cam_plane, row);
		row++;
	}
	
	// TODO Just create the player.plane here instead of saving it.
	col = 0;
	while(col < w)
	{
		camera_x = (2 * col / ((double) w) - 1);
		ray_start = vec2d_add(p->direction, vec2d_scalar_product(p->cam_plane, camera_x));
		p->rays[col] = raycaster_cast(p->position, ray_start, bound_check, p->meta);
		// printf("wall x: %f\n", p->rays[col].wall_x);
		col++;
	}
}
