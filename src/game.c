/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   game.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 22:35:05 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/09 03:31:20 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "timer.h"
#include <stdint.h>
#include <stdio.h>

void game_init(t_meta *meta)
{
	timer_init(&meta->tick_timer, mlx_get_time);
	timer_start(&meta->tick_timer);

	// Setup player initial position, later this correspond with the PLAYER_START in the map.
	meta->player.x = (meta->image->width / 2) - (PLAYER_WIDTH / 2);
	meta->player.y = (meta->image->height / 2) - (PLAYER_HEIGHT / 2);
}


// This function handles all the "simulation" type stuff such as moving players opening doors, etc.
void game_tick(t_meta *meta)
{
	t_player *p = &meta->player;

	double move = PLAYER_WALK_SPEED;

	if (mlx_is_key_down(meta->mlx, MLX_KEY_W))
		p->y -= move;
	if (mlx_is_key_down(meta->mlx, MLX_KEY_A))
		p->x -= move;

	if (mlx_is_key_down(meta->mlx, MLX_KEY_S))
		p->y += move + 1;
	if (mlx_is_key_down(meta->mlx, MLX_KEY_D))
		p->x += move + 1;
}

// TODO Implement a better game loop that fixes our screentearing issue.
void game_loop(void* param)
{
	t_meta *meta = param;

	// game logic every 20hz
	if (timer_delta(&meta->tick_timer) > TICK_RATE)
	{
		game_tick(meta);
		timer_start(&meta->tick_timer);
	}
	// Draw graphics as fast as possible when
	render_clear_bg(meta->image);
	render_map_grid(meta);
	render_player(meta);
}

