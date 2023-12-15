/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   game.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 22:35:05 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/15 16:12:06 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "meta.h"
#include "timer.h"
#include "vector.h"
#include <GLFW/glfw3.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <float.h>

void game_init(t_meta *meta)
{
	t_player* const p = &meta->player;

	timer_init(&meta->update_timer, mlx_get_time);
	timer_start(&meta->update_timer);

	// setup player stuff.
	p->meta = meta;

	// p->position[VEC_X] = (CELL_WIDTH + 1) * meta->map.player_start_x;
	// p->position[VEC_Y] = (CELL_HEIGHT + 1) * meta->map.player_start_y;

	// p->position[VEC_X] += (CELL_WIDTH / 2);
	// p->position[VEC_Y] += (CELL_HEIGHT / 2);

	p->position[VEC_X] = meta->map.player_start_x;
	p->position[VEC_Y] = meta->map.player_start_y;
	p->cam_plane = (t_vec2f) {0.0f, 0.66f};



	player_look(p, deg_to_rad(180.0f));
}

// This function handles all the "simulation" type stuff such as moving players opening doors, etc.
static void game_update(t_meta *meta, double time_delta)
{
	t_player *const p	= &meta->player;
	const float rotate	= (PLAYER_ROTATE_SPEED * time_delta);
	// float move = (PLAYER_WALK_SPEED * 10 * time_delta);
	float move = (PLAYER_WALK_SPEED * time_delta);

	if (mlx_is_key_down(meta->mlx, MLX_KEY_LEFT_SHIFT))
		move *= PLAYER_RUN_MODIFIER;
	if (mlx_is_key_down(meta->mlx, MLX_KEY_W))
		player_move(p, move * p->direction);
	if (mlx_is_key_down(meta->mlx, MLX_KEY_S))
		player_move(p, -move * p->direction);

	if (mlx_is_key_down(meta->mlx, MLX_KEY_A))
		player_move(p, vec2f_normalize(vec2f_rotate2d(p->angle_rad + (3 * PI / 2))) * move);
	if (mlx_is_key_down(meta->mlx, MLX_KEY_D))
		player_move(p, vec2f_normalize(vec2f_rotate2d(p->angle_rad + (PI / 2))) * move);

	if (mlx_is_key_down(meta->mlx, MLX_KEY_Q))
		player_look(p, -rotate);
	if (mlx_is_key_down(meta->mlx, MLX_KEY_E))
		player_look(p, rotate);
}


void game_loop(void* param)
{
	t_meta *const meta = param;
	// Time it took to draw a frame.
	double	frame_time;
	// Time it took for each iteration of the game_update loop.
	double	delta_time;

	frame_time = timer_delta(&meta->update_timer);

	// This approximation is slightly faster than `(frame_time > 0.000000)`.
	while (fabs(frame_time) >= 0.000005)
	{
		// `delta_time` is capped at `TICK_RATE`.
		delta_time = fmin(frame_time, TICK_RATE);
		game_update(meta, delta_time);

		frame_time -= delta_time;
	}
	timer_start(&meta->update_timer);

	render_clear_bg(meta->image);
	render_map_grid(meta->image, &meta->map);
	render_player_viewport(meta->image, &meta->player);
	render_player(meta->image, &meta->player);
}
