/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   game.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 22:35:05 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/20 18:41:37 by jboeve        ########   odam.nl         */

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

void	save_start_direction(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->direction.x = 0;
		player->direction.y = -1;
		player->data.plane.x = FOV;
		player->data.plane.y = 0;
	}
	else if (dir == 'S')
	{
		player->direction.x = 0;
		player->direction.y = 1;
		player->data.plane.x = FOV;
		player->data.plane.y = 0;
	}
	else if (dir == 'E')
	{
		player->direction.x = 1;
		player->direction.y = 0;
		player->data.plane.x = 0;
		player->data.plane.y = FOV;
	}
	else // W
	{
		player->direction.x = -1;
		player->direction.y = 0;
		player->data.plane.x = 0;
		player->data.plane.y = FOV;
	}
}

void game_init(t_meta *meta)
{
	t_player* const p = &meta->player;
	timer_init(&meta->update_timer, mlx_get_time);
	timer_start(&meta->update_timer);

	// setup player stuff.
	p->meta = meta;
	p->position.x = meta->map.player_start_x;
	p->position.y = meta->map.player_start_y;
	save_start_direction(&meta->player, meta->map.player_start_dir);
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
		if (col == 0)
			printf("LineHeight: %ld\n", meta->player.data.line_height);
		calculate_draw_start_and_end(meta, h);
		draw_column(meta, col, h);
		col++;
	}
}

void game_loop(void* param)
{
	t_meta *const meta = param;

	raycast_and_render(meta);
}
