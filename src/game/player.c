/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   player.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/10 02:25:34 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/21 00:11:03 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "libft.h"
#include "meta.h"
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>



bool	out_of_bounds(t_meta *meta, int x, int y)
{
	if (x < 0 || y < 0 || x >= (int)meta->map.width || y >= (int)meta->map.height)
		return (true);
	return (false);
}

// detects the hit too late
bool if_hits_wall(t_meta *meta, uint32_t x, uint32_t y)
{
	if (out_of_bounds(meta, x, y))
		return true;
	if (meta->map.level[find_index(meta, x, y)] == MAP_WALL)
	{
		return (true);
	}
	return (false);
}

void player_move_up(t_meta *meta)
{
	t_vec2d new_position;
	t_player* const player = &meta->player;

	new_position.x = (player->position.x + player->direction.x * PLAYER_MOV_SPEED);
	new_position.y = (player->position.y + player->direction.y * PLAYER_MOV_SPEED);
	if (!if_hits_wall(meta, new_position.x, new_position.y))
	{
		player->position.x += player->direction.x * PLAYER_MOV_SPEED;
		player->position.y += player->direction.y * PLAYER_MOV_SPEED;
	}
}

void player_move_down(t_meta *meta)
{
	t_vec2d new_position;
	
	t_player* const player = &meta->player;

	new_position.x = (player->position.x - player->direction.x * PLAYER_MOV_SPEED);
	new_position.y = (player->position.y - player->direction.y * PLAYER_MOV_SPEED);
	if (!if_hits_wall(meta, new_position.x, new_position.y))
	{
		player->position.x -= player->direction.x * PLAYER_MOV_SPEED;
		player->position.y -= player->direction.y * PLAYER_MOV_SPEED;
	}

}

void player_move_left(t_meta *meta)
{
	t_vec2d new_position;
	t_player* const player = &meta->player;

	new_position.x = (player->position.x - player->data.plane.x * PLAYER_MOV_SPEED);
	new_position.y = (player->position.y - player->data.plane.y * PLAYER_MOV_SPEED);
	if (!if_hits_wall(meta, new_position.x, new_position.y))
	{
		player->position.x -= player->data.plane.x * PLAYER_MOV_SPEED;
		player->position.y -= player->data.plane.y * PLAYER_MOV_SPEED;
	}
}

void player_move_right(t_meta *meta)
{
	t_vec2d new_position;
	t_player* const player = &meta->player;

	new_position.x = (player->position.x + player->data.plane.x * PLAYER_MOV_SPEED);
	new_position.y = (player->position.y + player->data.plane.y * PLAYER_MOV_SPEED);
	if (!if_hits_wall(meta, new_position.x, new_position.y))
	{
		player->position.x += player->data.plane.x * PLAYER_MOV_SPEED;
		player->position.y += player->data.plane.y * PLAYER_MOV_SPEED;
	}
}

// negative rotation parameter turns left vs positive rotation parameter turns right
void player_turn(t_meta *meta, double radiant)
{
	meta->player.direction = vec2d_rotate(meta->player.direction, radiant);
	meta->player.data.plane = vec2d_rotate(meta->player.data.plane, radiant);
}

