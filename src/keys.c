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

void keys_update(t_meta *meta, double time_delta)
{
	t_player *const p	= &meta->player;
	const float rotate	= (PLAYER_ROTATE_SPEED * time_delta);
	float move = (PLAYER_WALK_SPEED * time_delta);



	if (mlx_is_key_down(meta->mlx, MLX_KEY_LEFT_SHIFT))
		move *= PLAYER_RUN_MODIFIER;
	if (mlx_is_key_down(meta->mlx, MLX_KEY_W))
		player_move(p, move * p->direction);
	if (mlx_is_key_down(meta->mlx, MLX_KEY_S))
		player_move(p, -move * p->direction);

	if (mlx_is_key_down(meta->mlx, MLX_KEY_A))
		player_move(p, vec2f_normalize(vec2f_rotate2d(p->angle_rad + (3 * PI / 2))) * move);
	if (mlx_is_key_down(meta->mlx, MLX_KEY_D))
		player_move(p, vec2f_normalize(vec2f_rotate2d(p->angle_rad + (PI / 2))) * move);

	if (mlx_is_key_down(meta->mlx, MLX_KEY_Q))
		player_look(p, -rotate);
	if (mlx_is_key_down(meta->mlx, MLX_KEY_E))
		player_look(p, rotate);

}
