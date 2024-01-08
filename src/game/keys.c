/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:27:07 by yzaim             #+#    #+#             */
/*   Updated: 2024/01/08 15:27:11 by yzaim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "libft.h"
#include "meta.h"
#include "vector.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>

static void keys_handle_move(t_meta *meta, double delta_time)
{
	t_player* const p = &meta->player;
	float speed = PLAYER_MOVE_SPEED * delta_time;
	t_vec2d trans;
	bool pressed;

	pressed = false;
	ft_bzero(&trans, sizeof(t_vec2d));
	if (mlx_is_key_down(meta->mlx, MLX_KEY_LEFT_SHIFT))
		speed *= PLAYER_RUN_MODIFIER;
	if (mlx_is_key_down(meta->mlx, MLX_KEY_W))
	{
		pressed = true;
		trans = vec2d_add(trans, (t_vec2d) {p->direction.x * speed, p->direction.y * speed});
	}
	if (mlx_is_key_down(meta->mlx, MLX_KEY_S))
	{
		pressed = true;
		trans = vec2d_add(trans, (t_vec2d) {p->direction.x * -speed, p->direction.y * -speed});
	}
	if (mlx_is_key_down(meta->mlx, MLX_KEY_A))
	{
		pressed = true;
		trans = vec2d_add(trans, (t_vec2d) {(vec2d_rotate(p->direction, PI / 2).x) * -speed, (vec2d_rotate(p->direction, PI / 2).y) * -speed});
	}
	if (mlx_is_key_down(meta->mlx, MLX_KEY_D))
	{
		pressed = true;
		trans = vec2d_add(trans, (t_vec2d) {(vec2d_rotate(p->direction, PI / 2).x) * speed, (vec2d_rotate(p->direction, PI / 2).y) * speed});
	}

	if (pressed)
		player_move(p, trans);
}
void render_test(t_meta *meta);

void keys_handle(t_meta *meta, double delta_time)
{
	t_player* const p = &meta->player;
	float rotate_speed = PLAYER_ROTATE_SPEED * delta_time;

	if (mlx_is_key_down(meta->mlx, MLX_KEY_LEFT_CONTROL))
		rotate_speed /= PLAYER_ROTATE_MODIFIER;
	if (mlx_is_key_down(meta->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(meta->mlx);
	if (mlx_is_key_down(meta->mlx, MLX_KEY_Q))
		player_turn(p, -rotate_speed);
	if (mlx_is_key_down(meta->mlx, MLX_KEY_E))
		player_turn(p, rotate_speed);
	keys_handle_move(meta, delta_time);
}


void cursor_hook(double xpos, double ypos, void *param)
{
	t_meta *meta = param;
	const int32_t center = meta->image->width / 2;
	const float rot = 0.0004f;
	float speed;

	(void) ypos;

	if (xpos > center)
		speed = rot * (xpos - center);
	else
		speed = -rot * (center - xpos);

	player_turn(&meta->player, speed);
	mlx_set_mouse_pos(meta->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}
