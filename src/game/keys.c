/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   keys.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/12/15 14:05:30 by jboeve        #+#    #+#                 */
/*   Updated: 2023/12/21 00:16:10 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include <stdio.h>

void keys_handle(t_meta *meta, double time_delta)
{
	if (mlx_is_key_down(meta->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(meta->mlx);
	if (mlx_is_key_down(meta->mlx, MLX_KEY_W))
	{
		player_move_up(meta);
	}
	if (mlx_is_key_down(meta->mlx, MLX_KEY_S))
	{
		player_move_down(meta);
	}
	if (mlx_is_key_down(meta->mlx, MLX_KEY_A))
	{
		player_move_left(meta);
	}
	if (mlx_is_key_down(meta->mlx, MLX_KEY_D))
	{
		player_move_right(meta);
	}
	if (mlx_is_key_down(meta->mlx, MLX_KEY_Q))
	{
		player_turn(meta, -PLAYER_ROTATE_SPEED);
	}
	if (mlx_is_key_down(meta->mlx, MLX_KEY_E))
	{
		player_turn(meta, PLAYER_ROTATE_SPEED);
	}
}
