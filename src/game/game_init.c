/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_init.c                                       :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:26:51 by yzaim         #+#    #+#                 */
/*   Updated: 2024/03/03 20:59:58 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "meta.h"
#include "timer.h"
#include "vector.h"
#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

static void	set_values(t_player *p, t_vec2d dir, t_vec2d cam)
{
	p->direction.x = dir.x;
	p->direction.y = dir.y;
	p->cam_plane.x = cam.x;
	p->cam_plane.y = cam.y;
}

/* Setting player direction.x to non-zero fixes door issue when 'player_turn' 
has not been called */
void	set_player_start_position(t_player *p, char dir)
{
	if (dir == 'N')
	{
		set_values(p, (t_vec2d){0.0000001, -1.0}, (t_vec2d){FOV, 0.0});
	}
	else if (dir == 'S')
	{
		set_values(p, (t_vec2d){0.0000001, 1}, (t_vec2d){-FOV, 0.0});
	}
	else if (dir == 'E')
	{
		set_values(p, (t_vec2d){1.0000001, 0}, (t_vec2d){0.0, FOV});
	}
	else
	{
		set_values(p, (t_vec2d){-1.0000001, 0}, (t_vec2d){0.0, -FOV});
	}
	p->position = vec2u_to_vec2d(p->meta->map.player_start);
	p->position.x += 0.5;
	p->position.y += 0.5;
}

int	game_init(t_meta *meta)
{
	t_player *const	p = &meta->player;

	timer_init(&meta->update_timer, mlx_get_time);
	timer_start(&meta->update_timer);
	if (init_sprites(meta->attributes.sprite_count, &meta->player.sprite_order, \
		&meta->player.sprite_dist))
	{
		return (false);
	}
	p->meta = meta;
	set_player_start_position(&meta->player, meta->map.player_start_dir);
	player_move(p, (t_vec2d){0.0, 0.0});
	return (true);
}
