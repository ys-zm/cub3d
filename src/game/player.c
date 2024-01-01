/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   player.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/10 02:25:34 by joppe         #+#    #+#                 */
/*   Updated: 2024/01/01 15:08:22 by joppe         ########   odam.nl         */
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

void player_move(t_meta *meta, t_vec2d transform)
{
	t_player* const	p = &meta->player;
	t_vec2d			new_position;

	new_position.x = (p->position.x + (transform.x));
	new_position.y = (p->position.y + (transform.y));
	if (!if_hits_wall(meta, new_position.x, new_position.y))
	{
		p->position.x += transform.x;
		p->position.y += transform.y;
	}
}

// negative rotation parameter turns left vs positive rotation parameter turns right
void player_turn(t_meta *meta, float radiant)
{
	meta->player.direction = vec2d_rotate(meta->player.direction, radiant);
	meta->player.data.plane = vec2d_rotate(meta->player.data.plane, radiant);
}
