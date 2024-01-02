/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   game.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 22:35:05 by joppe         #+#    #+#                 */
/*   Updated: 2024/01/02 19:49:20 by joppe         ########   odam.nl         */

/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "timer.h"
#include "vector.h"
#include <math.h>
#include <unistd.h>

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
	player_move(p, (t_vec2d) {0.0, 0.0});
}

void game_init(t_meta *meta)
{
	t_player* const p = &meta->player;
	timer_init(&meta->update_timer, mlx_get_time);
	timer_start(&meta->update_timer);

	p->meta = meta;
	set_player_start_position(&meta->player, meta->map.player_start_dir);
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
	render_player_viewport(meta->image, &meta->player);
}
