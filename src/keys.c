/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   keys.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/12/15 14:05:30 by jboeve        #+#    #+#                 */
/*   Updated: 2023/12/15 14:24:11 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include <stdio.h>

void keys_update(mlx_key_data_t keydata, void *param)
{
	t_meta *meta;
	meta = (t_meta *) param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(meta->mlx);
	if (mlx_is_key_down(meta->mlx, MLX_KEY_W) == true)
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
		player_turn(meta, PLAYER_ROTATE_SPEED * -1);
	}
	if (mlx_is_key_down(meta->mlx, MLX_KEY_E))
	{
		player_turn(meta, PLAYER_ROTATE_SPEED);
	}
}
