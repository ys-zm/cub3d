/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                            :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:26:51 by yzaim             #+#    #+#             */
/*   Updated: 2024/01/27 20:37:45 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "meta.h"
#include "timer.h"
#include "vector.h"
#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <unistd.h>
#include "test_utils.h"

void	set_player_start_position(t_player *p, char dir)
{
	if (dir == 'N')
	{
		p->direction.x = 0;
		p->direction.y = -1;
		p->cam_plane.x = FOV;
		p->cam_plane.y = 0;
	}
	else if (dir == 'S')
	{
		p->direction.x = 0;
		p->direction.y = 1;
		p->cam_plane.x = FOV;
		p->cam_plane.y = 0;
	}
	else if (dir == 'E')
	{
		p->direction.x = 1;
		p->direction.y = 0;
		p->cam_plane.x = 0;
		p->cam_plane.y = FOV;
	}
	else // W
	{
		p->direction.x = -1;
		p->direction.y = 0;
		p->cam_plane.x = 0;
		p->cam_plane.y = FOV;
	}
	p->position = vec2u_to_vec2d(p->meta->map.player_start);
	// center player in tile.
	p->position.x += 0.5;
	p->position.y += 0.5;
}




void swap_tex(mlx_texture_t *tex)
{
	assert(tex->width == tex->height);

	for (size_t x = 0; x < tex->width; x++)
	{
		for (size_t y = 0; y < x; y++)
		{
			uint32_t pixel = tex->pixels[(tex->width * y + x) * BPP];
			tex->pixels[(tex->width * y + x) * BPP] = tex->pixels[(tex->width * x + y) * BPP];
			tex->pixels[(tex->width * x + y) * BPP] = pixel;
		}
	}
}

void game_init(t_meta *meta)
{
	t_player* const p = &meta->player;
	timer_init(&meta->update_timer, mlx_get_time);
	timer_start(&meta->update_timer);

	p->meta = meta;
	set_player_start_position(&meta->player, meta->map.player_start_dir);
	player_move(p, (t_vec2d) {0.0, 0.0}); // to draw the image at the start (?)


	meta->container.tex = mlx_create_tex(meta->mlx);
	meta->container.pixels = meta->attributes.w.tex->pixels;
}

static void game_update(t_meta *meta, double time_delta)
{
	keys_handle(meta, time_delta);
}

void game_loop(void* param)
{
	t_meta *const	meta = param;
	double			frame_time;
	double			delta_time;

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
	render_minimap(&meta->minimap, &meta->map, &meta->player);
	render_viewport(meta->image, &meta->player);
}
