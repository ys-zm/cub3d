/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   input.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 23:03:00 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/14 19:40:09 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "meta.h"
#include "vector.h"
#include <stdint.h>
#include <stdio.h>

void key_hook(mlx_key_data_t keydata, void* param)
{
	t_meta *meta = param;

	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(meta->mlx);
}


void cursor_hook(double xpos, double ypos, void* param)
{
	t_meta *meta = param;

	if (mlx_is_mouse_down(meta->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		t_vec2f drag = (t_vec2f){ xpos, ypos};
		player_move(&meta->player, drag - meta->player.position);
	}
}

