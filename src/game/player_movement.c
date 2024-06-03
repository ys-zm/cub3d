/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   player_movement.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/03/01 12:41:56 by jboeve        #+#    #+#                 */
/*   Updated: 2024/05/30 16:23:06 by yesimzaim     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "vector.h"

static void	player_move_cast(t_ray *r, t_vec2d transform, t_player *p)
{
	const int		comp = (r->hit_side == SIDE_E || r->hit_side == SIDE_W);
	const t_vec2d	normal = {comp, !comp};
	const double	dot_product = vec2d_dot_product(transform, normal);
	const t_vec2d	delta_pos = {transform.x - normal.x * dot_product, transform.y - normal.y * dot_product};

	*r = raycaster_cast(p->position, vec2d_normalize(transform), bound_check, p->meta);
	if (r->hit_cell == MAP_DOOR_CLOSED && r->length < 0.5)
		return ;
	if (r->length > 0.3)
	{
		p->position.x += delta_pos.x;
		p->position.y += delta_pos.y;
	}
}

void	player_move(t_player *p, t_vec2d transform)
{
	t_ray	r;

	r = raycaster_cast(p->position, vec2d_normalize(transform), bound_check, p->meta);
	if (r.hit_cell == MAP_DOOR_CLOSED && r.length < 1.0)
		return ;
	if (r.length > 0.5)
		p->position = vec2d_add(p->position, transform);
	else
	{
		player_move_cast(&r, transform, p);
	}
	player_raycast(p);
}

void	player_turn(t_player *p, float radiant)
{
	p->direction = vec2d_rotate(p->direction, radiant);
	p->cam_plane = vec2d_rotate(p->cam_plane, radiant);
	player_raycast(p);
}
