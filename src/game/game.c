/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:26:51 by yzaim         #+#    #+#                 */
/*   Updated: 2024/02/28 17:39:45 by yzaim         ########   odam.nl         */
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

void	swap_tex(mlx_texture_t *tex)
{
	int			x;
	int			y;
	uint32_t	pixel;

	assert(tex->width == tex->height);
	x = 0;
	while (x < tex->width)
	{
		y = 0;
		while (y < x)
		{
			pixel = tex->pixels[(tex->width * y + x) * BPP];
			tex->pixels[(tex->width * y + x) * BPP] = \
			tex->pixels[(tex->width * x + y) * BPP];
			tex->pixels[(tex->width * x + y) * BPP] = pixel;
			y++;
		}
		x++;
	}
}

static void	game_update(t_meta *meta, double time_delta)
{
	keys_handle(meta, time_delta);
}

void	game_loop(void* param)
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
	sprite_calculate(&meta->player);
}
