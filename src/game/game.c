/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.c                                            :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:26:51 by yzaim         #+#    #+#                 */
/*   Updated: 2024/05/30 20:59:03 by joppe         ########   odam.nl         */
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

static void	game_update(t_meta *meta, double time_delta)
{
	keys_handle(meta, time_delta);
}

void	game_loop(void *param)
{
	t_meta *const	meta = param;
	double			frame_time;
	double			delta_time;

	frame_time = timer_delta(&meta->update_timer);
	while (fabs(frame_time) >= 0.000005)
	{
		delta_time = fmin(frame_time, TICK_RATE);
		game_update(meta, delta_time);
		frame_time -= delta_time;
	}
	timer_start(&meta->update_timer);
	render_minimap(&meta->minimap, &meta->map, &meta->player);
	render_viewport(meta->image, &meta->player);
}
