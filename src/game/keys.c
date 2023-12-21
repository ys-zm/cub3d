/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   keys.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/12/15 14:05:30 by jboeve        #+#    #+#                 */
/*   Updated: 2023/12/21 01:18:05 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"

void keys_handle(t_meta *meta, double delta_time)
{
	t_player* const p = &meta->player;
	float speed = PLAYER_MOVE_SPEED * delta_time;
	float rotate_speed = PLAYER_ROTATE_SPEED * delta_time;

	if (mlx_is_key_down(meta->mlx, MLX_KEY_LEFT_SHIFT))
		speed *= PLAYER_RUN_MODIFIER;
	if (mlx_is_key_down(meta->mlx, MLX_KEY_LEFT_CONTROL))
		rotate_speed /= PLAYER_ROTATE_MODIFIER;
	if (mlx_is_key_down(meta->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(meta->mlx);
	if (mlx_is_key_down(meta->mlx, MLX_KEY_W))
	{
		player_move(meta, (t_vec2d) {p->direction.x * speed, p->direction.y * speed});
	}
	if (mlx_is_key_down(meta->mlx, MLX_KEY_S))
	{
		player_move(meta, (t_vec2d) {p->direction.x * -speed, p->direction.y * -speed});
	}
	if (mlx_is_key_down(meta->mlx, MLX_KEY_A))
	{
		player_move(meta, (t_vec2d) {(vec2d_rotate(p->direction, PI / 2).x) * -speed, (vec2d_rotate(p->direction, PI / 2).y) * -speed});
	}
	if (mlx_is_key_down(meta->mlx, MLX_KEY_D))
	{
		player_move(meta, (t_vec2d) {(vec2d_rotate(p->direction, PI / 2).x) * speed, (vec2d_rotate(p->direction, PI / 2).y) * speed});
	}
	if (mlx_is_key_down(meta->mlx, MLX_KEY_Q))
	{
		player_turn(meta, -rotate_speed);
	}
	if (mlx_is_key_down(meta->mlx, MLX_KEY_E))
	{
		player_turn(meta, rotate_speed);
	}
}
