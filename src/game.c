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

void game_init(t_meta *meta)
{
	timer_init(&meta->tick_timer, mlx_get_time);
	timer_start(&meta->tick_timer);

	// Setup player initial position, later this correspond with the PLAYER_START in the map.
	meta->player.x = (meta->image->width / 2) - (PLAYER_WIDTH / 2);
	meta->player.y = (meta->image->height / 2) - (PLAYER_HEIGHT / 2);
}


// This function handles all the "simulation" type stuff such as moving players opening doors, etc.
void game_tick(t_meta *meta, double_t time_delta)
{
	t_player *p = &meta->player;

	float move = (PLAYER_WALK_SPEED * time_delta);


	if (mlx_is_key_down(meta->mlx, MLX_KEY_W))
		p->y -= move;
	if (mlx_is_key_down(meta->mlx, MLX_KEY_A))
		p->x -= move;

	if (mlx_is_key_down(meta->mlx, MLX_KEY_S))
		p->y += move;
	if (mlx_is_key_down(meta->mlx, MLX_KEY_D))
		p->x += move;
}

double dt = 1 / 60.0;

double currentTime = -1.0;

// TODO Implement a better game loop that fixes our screentearing issue.
void game_loop(void* param)
{
	t_meta *meta = param;


	if (currentTime == -1.0)
		currentTime = mlx_get_time();

	double newTime = mlx_get_time();
	double frameTime = newTime - currentTime;
	currentTime = newTime;


	size_t i = 0;

	while (frameTime > 0.0)
	{
		float deltaTime = fmin(frameTime, dt);
		game_tick(meta, deltaTime);
		frameTime -= deltaTime;
		i++;
	}
	printf("ticks [%ld]\n", i);

	render_clear_bg(meta->image);
	render_map_grid(meta);
	render_player(meta);
}


