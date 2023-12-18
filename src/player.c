/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   player.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/10 02:25:34 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/15 15:34:10 by jboeve        ########   odam.nl         */
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

bool if_hits_wall(t_meta *meta, uint32_t x, uint32_t y)
{
	if (meta->map.level[find_index(meta, x, y)] == MAP_WALL)
		return (true);
	return (false);
}

void player_move_up(t_meta *meta)
{
	t_point new_position;

	new_position.x = (int)(meta->player.position.x + meta->player.direction.x * PLAYER_MOV_SPEED);
	new_position.y = (int)(meta->player.position.y + meta->player.direction.y * PLAYER_MOV_SPEED);
	if (!if_hits_wall(meta, new_position.x, new_position.y))
	{
		meta->player.position.x += meta->player.direction.x * PLAYER_MOV_SPEED;
		meta->player.position.y += meta->player.direction.y * PLAYER_MOV_SPEED;
	}
}

void player_move_down(t_meta *meta)
{
	t_point new_position;

	new_position.x = (int)(meta->player.position.x - meta->player.direction.x * PLAYER_MOV_SPEED);
	new_position.y = (int)(meta->player.position.y - meta->player.direction.y * PLAYER_MOV_SPEED);
	if (!if_hits_wall(meta, new_position.x, new_position.y))
	{
		meta->player.position.x -= meta->player.direction.x * PLAYER_MOV_SPEED;
		meta->player.position.y -= meta->player.direction.y * PLAYER_MOV_SPEED;
	}

}

void player_move_left(t_meta *meta)
{
	t_point new_position;

	new_position.x = (int)(meta->player.position.x - meta->data.plane.x * PLAYER_MOV_SPEED);
	new_position.y = (int)(meta->player.position.y - meta->data.plane.y * PLAYER_MOV_SPEED);
	if (!if_hits_wall(meta, new_position.x, new_position.y))
	{
		meta->player.position.x -= meta->data.plane.x * PLAYER_MOV_SPEED;
		meta->player.position.y -= meta->data.plane.y * PLAYER_MOV_SPEED;
	}
}

void player_move_right(t_meta *meta)
{
	t_point new_position;

	new_position.x = (int)(meta->player.position.x + meta->data.plane.x * PLAYER_MOV_SPEED);
	new_position.y = (int)(meta->player.position.y + meta->data.plane.y * PLAYER_MOV_SPEED);
	if (!if_hits_wall(meta, new_position.x, new_position.y))
	{
		meta->player.position.x += meta->data.plane.x * PLAYER_MOV_SPEED;
		meta->player.position.y += meta->data.plane.y * PLAYER_MOV_SPEED;
	}
}

t_vector vector_rotate(t_vector old, double radiant)
{
	t_vector	new;

	new.x = old.x * cos(radiant) - old.y * sin(radiant);
	new.y = old.x * sin(radiant) + old.y * cos(radiant);
	return (new);
}
// negative rotation parameter turns left vs positive rotation parameter turns right
void player_turn(t_meta *meta, double radiant)
{
	meta->player.direction = vector_rotate(meta->player.direction, radiant);
	meta->data.plane = vector_rotate(meta->data.plane, radiant);
}

