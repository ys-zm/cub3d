/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                          :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:27:23 by yzaim             #+#    #+#             */
/*   Updated: 2024/01/18 17:10:32 by jboeve        ########   odam.nl         */
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

	const double margin = 0.005;

	float angle = (atan2(p->direction.x, p->direction.y) / PI * 180 + 180);
	printf("angle [%f]\n", angle);
	if (r.length > .5)
	{
		p->position.y += transform.y;
		p->position.x += transform.x;
	}
	else if (r.length > .1)
	{
		printf("angle [%f]\n", angle);

		double res = 0.0;

		// Colission with a wall the y-axis
		if ((angle > 0 && angle < 45) || (angle > 315))
		{
			printf("Gliding N\n");
			 res = transform.x * -p->direction.y;
			r = raycaster_cast(p->position, (t_vec2d) {res, 0.0}, bound_check, p->meta);
			if (r.length > .1)
				p->position.x += res;
		}
		else if (angle > 90 && angle < 270)
		{
			printf("Gliding S\n");
			res = transform.x * p->direction.y;
			r = raycaster_cast(p->position, (t_vec2d) {res, 0.0}, bound_check, p->meta);
			if (r.length > .1)
				p->position.x += res;
		}


		// if (angle == 1 || angle == 2)
		// {
		// 	double res = transform.y * -p->direction.x;
		// 	r = raycaster_cast(p->position, (t_vec2d) {0.0, res}, bound_check, p->meta);
		// 	p->position.y += res;
		// }
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
		p->rays[col] = raycaster_cast(p->position, ray_start, bound_check, p->meta);
		// printf("wall x: %f\n", p->rays[col].wall_x);
		col++;
	}
}
