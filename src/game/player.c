/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                          :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:27:23 by yzaim             #+#    #+#             */
/*   Updated: 2024/01/20 00:22:42 by joppe         ########   odam.nl         */
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

void print_angle(t_player *p)
{
	// NORTH = 0
	const float angle = (atan2(p->direction.x, p->direction.y) / PI * 180 + 180);

	if (angle > 45.0 && angle < 135.0)
	{
		printf("N\n");
	}
	else if (angle > 135.0 && angle < 225.0)
	{
		printf("E\n");
	}
	else if (angle > 225.0 && angle < 315.0)
	{
		printf("S\n");
	}
	else if (angle > 315.0 || angle < 45.0)
	{
		printf("W\n");
	}
}

void player_move(t_player *p, t_vec2d transform)
{
	t_ray r = raycaster_cast(p->position, vec2d_normalize(transform), bound_check, p->meta);

	if (r.length > .5)
	{
		p->position.y += transform.y;
		p->position.x += transform.x;
	}
	print_angle(p);
	player_raycast(p);
}

// negative rotation parameter turns left vs positive rotation parameter turns right
void player_turn(t_player *p, float radiant)
{
	p->direction = vec2d_rotate(p->direction, radiant);
	p->cam_plane = vec2d_rotate(p->cam_plane, radiant);
	print_angle(p);
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
		p->rays[col] = raycaster_cast(p->position, ray_start, bound_check, p->meta);
		// printf("wall x: %f\n", p->rays[col].wall_x);
		col++;
	}
}
