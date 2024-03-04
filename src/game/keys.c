/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:27:07 by yzaim         #+#    #+#                 */
/*   Updated: 2024/03/04 12:31:30 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "libft.h"
#include "meta.h"
#include "vector.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>

bool	is_pressed(t_meta *meta)
{
	return (mlx_is_key_down(meta->mlx, MLX_KEY_W) || \
			mlx_is_key_down(meta->mlx, MLX_KEY_S) || \
			mlx_is_key_down(meta->mlx, MLX_KEY_A) || \
			mlx_is_key_down(meta->mlx, MLX_KEY_D));
}

static void	keys_handle_move(t_meta *meta, double delta_time)
{
	t_player *const	p = &meta->player;
	t_vec2d			trans;
	float			speed;
	const bool		pressed = is_pressed(meta);

	speed = PLAYER_MOVE_SPEED * delta_time;
	ft_bzero(&trans, sizeof(t_vec2d));
	if (mlx_is_key_down(meta->mlx, MLX_KEY_LEFT_SHIFT))
		speed *= PLAYER_RUN_MODIFIER;
	if (mlx_is_key_down(meta->mlx, MLX_KEY_W))
		trans = vec2d_add(trans, \
				(t_vec2d){p->direction.x * speed, p->direction.y * speed});
	if (mlx_is_key_down(meta->mlx, MLX_KEY_S))
		trans = vec2d_add(trans, \
				(t_vec2d){p->direction.x * -speed, p->direction.y * -speed});
	if (mlx_is_key_down(meta->mlx, MLX_KEY_A))
		trans = vec2d_add(trans, \
				(t_vec2d){(vec2d_rotate(p->direction, PI / 2).x) * -speed, \
				(vec2d_rotate(p->direction, PI / 2).y) * -speed});
	if (mlx_is_key_down(meta->mlx, MLX_KEY_D))
		trans = vec2d_add(trans, \
				(t_vec2d){(vec2d_rotate(p->direction, PI / 2).x) * speed, \
				(vec2d_rotate(p->direction, PI / 2).y) * speed});
	if (pressed)
		player_move(p, trans);
}

static bool	key_pressed(t_meta *meta, keys_t k)
{
	bool	*old_state;

	old_state = &meta->key_states[k - MLX_KEY_SPACE];
	if (mlx_is_key_down(meta->mlx, k) && !*old_state)
	{
		*old_state = true;
		return (true);
	}
	else if (!mlx_is_key_down(meta->mlx, k) && *old_state)
		*old_state = false;
	return (false);
}

void	keys_handle(t_meta *meta, double delta_time)
{
	t_player *const	p = &meta->player;
	float			rotate_speed;

	rotate_speed = PLAYER_ROTATE_SPEED * delta_time;
	if (mlx_is_key_down(meta->mlx, MLX_KEY_LEFT_CONTROL))
		rotate_speed /= PLAYER_ROTATE_MODIFIER;
	if (mlx_is_key_down(meta->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(meta->mlx);
	if (mlx_is_key_down(meta->mlx, MLX_KEY_Q) || mlx_is_key_down(meta->mlx, MLX_KEY_LEFT))
		player_turn(p, -rotate_speed);
	if (mlx_is_key_down(meta->mlx, MLX_KEY_E) || mlx_is_key_down(meta->mlx, MLX_KEY_RIGHT))
		player_turn(p, rotate_speed);
	if (key_pressed(meta, MLX_KEY_F))
		player_interact(p);
	keys_handle_move(meta, delta_time);
}

void	cursor_hook(double xpos, double ypos, void *param)
{
	t_meta *const	meta = param;
	const int32_t	center = meta->image->width / 2;
	const float		rot = 0.0006f;
	float			speed;

	(void) ypos;
	if (xpos > center)
		speed = rot * (xpos - center);
	else
		speed = -rot * (center - xpos);
	player_turn(&meta->player, speed);
	mlx_set_mouse_pos(meta->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}
