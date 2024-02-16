/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                          :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:27:23 by yzaim             #+#    #+#             */
/*   Updated: 2024/02/16 22:11:03 by joppe         ########   odam.nl         */
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

t_cell_type bound_check(const void *param, uint32_t x, uint32_t y)
{
	t_meta *const meta = (t_meta *) param;
	t_cell_type cell;

	if (x < meta->map.width && y < meta->map.height)
	{
		cell = meta->map.level[(y * meta->map.width) + x];
		if (cell == MAP_WALL || cell == MAP_DOOR_CLOSED)
			return (cell);
		else
			return (0);
	}
	else
	{
		UNIMPLEMENTED("Map out of bounds.");
	}
}

t_cell_type bound_check_interact(const void *param, uint32_t x, uint32_t y)
{
	t_meta *const meta = (t_meta *) param;
	t_cell_type cur_cell;

	if (x < meta->map.width && y < meta->map.height)
	{
		cur_cell = meta->map.level[(y * meta->map.width) + x];
		if (cur_cell == MAP_WALL || cur_cell == MAP_DOOR_CLOSED || cur_cell == MAP_DOOR_OPEN)
			return (cur_cell);
		else
			return (0);
	}
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

	if (r.length > 0.5)
		p->position = vec2d_add(p->position, transform);
	else
	{
		const int		comp = (r.hit_side == SIDE_N || r.hit_side == SIDE_S);
		const t_vec2d	normal = {comp, !comp}; // 1, 0 // 0, 1
		const double 	dot_product = vec2d_dot_product(transform, normal);


		t_vec2d delta_pos;
		delta_pos.x = transform.x - normal.x * dot_product;
		delta_pos.y = transform.y - normal.y * dot_product;
		r = raycaster_cast(p->position, vec2d_normalize(transform), bound_check, p->meta);

		if (r.length > 0.3)
		{
			p->position.x += delta_pos.x;
			p->position.y += delta_pos.y;
		}
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

void player_interact(t_player *p)
{
	t_ray *r = &p->interact_ray;

	if (((char *) r)[0])
	{
		world_interact(p, r->end);
		player_raycast(p);
	}
}


static void player_interactable_raycast(t_player *p)
{
	t_ray *r = &p->interact_ray;

	*r = raycaster_cast(p->position, p->direction, bound_check_interact, p->meta);

	// print_hit_side("side", r->hit_side);

	if (world_is_interactable(r->hit_cell) && r->length < 1.5)
	{
		// print message to screen
		// print_ray("interact ray", r);
		// printf("Press F to interact with [%s]\n",  CELL_NAMES[r->hit_cell]);
	}
	else
		ft_bzero(r, sizeof(t_ray));


}

void player_raycast(t_player *p)
{
	uint32_t	w = p->meta->image->width;
	uint32_t	h = p->meta->image->height;
	uint32_t	col;
	uint32_t	row;
	t_vec2d		ray_start;
	double		camera_x;


	player_interactable_raycast(p);

	row = 0;
	while (row < h)
	{
		p->vrays[row] = floorcaster(p->position, p->direction, p->cam_plane, row);
		row++;
	}
	p->should_render = true;
	
	// TODO Just create the player.plane here instead of saving it.
	col = 0;
	while (col < p->meta->image->width)
	{
		camera_x = (2 * col / ((double) p->meta->image->width) - 1);
		ray_start = vec2d_add(p->direction, vec2d_scalar_product(p->cam_plane, camera_x));
		p->hrays[col] = raycaster_cast(p->position, ray_start, bound_check, p->meta);
		// printf("wall x: %f\n", p->rays[col].wall_x);
		p->z_buffer[col] = p->hrays[col].length;
		col++;
	}	

	sprite_calculate(p);
}
