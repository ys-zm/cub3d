/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   game.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 22:35:05 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/21 00:24:48 by joppe         ########   odam.nl         */

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

void	set_player_start_position(t_player *p, char dir)
{
	if (dir == 'N')
	{
		p->direction.x = 0;
		p->direction.y = -1;
		p->data.plane.x = FOV;
		p->data.plane.y = 0;
	}
	else if (dir == 'S')
	{
		p->direction.x = 0;
		p->direction.y = 1;
		p->data.plane.x = FOV;
		p->data.plane.y = 0;
	}
	else if (dir == 'E')
	{
		p->direction.x = 1;
		p->direction.y = 0;
		p->data.plane.x = 0;
		p->data.plane.y = FOV;
	}
	else // W
	{
		p->direction.x = -1;
		p->direction.y = 0;
		p->data.plane.x = 0;
		p->data.plane.y = FOV;
	}
	p->position = vec2u_to_vec2d(p->meta->map.player_start);
}

void game_init(t_meta *meta)
{
	t_player* const p = &meta->player;
	timer_init(&meta->update_timer, mlx_get_time);
	timer_start(&meta->update_timer);

	p->meta = meta;
	set_player_start_position(&meta->player, meta->map.player_start_dir);
}

void raycast_and_render(t_meta *meta)
{	
	t_player *player = &meta->player;
	uint32_t w = WINDOW_WIDTH;
	uint32_t h = WINDOW_HEIGHT;
	uint32_t col;

	col = 0;
	while(col < w)
	{
		player->data.camera_x = 2 * col / (double)w - 1 ; //x-coordinate in camera space
		player->data.ray_direction = vec2d_add(player->direction, vec2d_scalar_product(player->data.plane, player->data.camera_x));
		player->data.map_pos.x = (int)player->position.x;
		player->data.map_pos.y = (int)player->position.y;
		calculate_delta_dist(&meta->player);
		calculate_side_distance(&meta->player);
		dda_algorithm(meta);

		// save calculations of line height and render else where?
		calculate_line_height(&meta->player.data, h);
		calculate_draw_start_and_end(meta, h);
		draw_column(meta, col, h);
		col++;
	}
}

static void game_update(t_meta *meta, double time_delta)
{
	keys_handle(meta, time_delta);
}

void game_loop(void* param)
{
	t_meta *const meta = param;

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
	render_minimap(meta->image, &meta->map);
	raycast_and_render(meta);
}
