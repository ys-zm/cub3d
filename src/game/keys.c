/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   keys.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/12/15 14:05:30 by jboeve        #+#    #+#                 */
/*   Updated: 2023/12/21 01:58:42 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "meta.h"
#include <math.h>
#include <stdio.h>

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

// void mlx_set_cursor_mode(mlx_t* mlx, mouse_mode_t mode);
// void mlx_set_mouse_pos(mlx_t* mlx, int32_t x, int32_t y);
void mouse_hook(double xpos, double ypos, void* param)
{
	t_meta *meta = param;
	static double x_old = 0;
	const float rotate_speed = 0.200f;
	static bool going_right = false;

	static double time_old = 0;
	if (time_old == 0)
		time_old = mlx_get_time();
	if (x_old == 0)
		x_old = xpos;

	if (mlx_get_time() - time_old > 0.20)
		time_old = mlx_get_time();

	float delta_time = mlx_get_time() - time_old;
	float speed = delta_time * fabs(x_old - xpos) * rotate_speed;
	if (xpos > x_old)
	{
		if (!going_right)
		{
			printf("going left\n");
			delta_time = mlx_get_time() - time_old;
			speed = delta_time * fabs(x_old - xpos) * rotate_speed;
		}
		player_turn(meta, -speed);
		going_right = true;
	}
	else
	{
		if (going_right)
		{
			printf("going right\n");
			delta_time = mlx_get_time() - time_old;
			speed = delta_time * fabs(x_old - xpos) * rotate_speed;
		}
		player_turn(meta, speed);
		going_right = false;
	}
	// printf("delta_time [%lf]\n", delta_time);
	// printf("speed [%lf]\n", speed);
	// printf("mousepos [%lf]\n", xpos);
	time_old = mlx_get_time();
	mlx_set_mouse_pos(meta->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT /2);
	x_old = xpos;
}
