/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   game.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 22:35:05 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/09 20:10:34 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "meta.h"
#include "timer.h"
#include <GLFW/glfw3.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <float.h>

void game_init(t_meta *meta)
{
	timer_init(&meta->update_timer, mlx_get_time);
	timer_start(&meta->update_timer);

	// Setup player initial position, later this correspond with the PLAYER_START in the map.
	meta->player.x = (uint32_t) (meta->image->width / 2) - ((float) PLAYER_WIDTH / 2);
	meta->player.y = (uint32_t) (meta->image->height / 2) - ((float) PLAYER_HEIGHT / 2);
}


// This function handles all the "simulation" type stuff such as moving players opening doors, etc.
void game_update(t_meta *meta, double_t time_delta)
{
	t_player *const p = &meta->player;
	const float move = (PLAYER_WALK_SPEED * time_delta);

	if (mlx_is_key_down(meta->mlx, MLX_KEY_W))
		p->y -= move;
	if (mlx_is_key_down(meta->mlx, MLX_KEY_A))
		p->x -= move;
	if (mlx_is_key_down(meta->mlx, MLX_KEY_S))
		p->y += move;
	if (mlx_is_key_down(meta->mlx, MLX_KEY_D))
		p->x += move;
}


void game_loop(void* param)
{
	t_meta *const meta = param;
	double	frame_time;
	double	delta_time;

	frame_time = timer_delta(&meta->update_timer);

	while (fabs(frame_time) >= 0.000005)
	{
		delta_time = fmin(frame_time, TICK_RATE);
		game_update(meta, delta_time);
		frame_time -= delta_time;
	}
	timer_start(&meta->update_timer);

	render_clear_bg(meta->image);
	render_map_grid(meta);
	render_player(meta);
}
