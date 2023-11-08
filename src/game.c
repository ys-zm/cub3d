/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   game.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 22:35:05 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/08 22:59:35 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "timer.h"
#include <stdio.h>

void game_init(t_meta *meta)
{
	timer_init(&meta->tick_timer, mlx_get_time);
	timer_start(&meta->tick_timer);
}

void game_loop(void* param)
{
	t_meta *meta = param;

	// game logic every 20hz
	if (timer_delta(&meta->tick_timer) > TICK_RATE)
	{
		printf("tick\n");
		timer_start(&meta->tick_timer);
	}
	printf("render\n");
	// draw graphics as fast as possible


}

