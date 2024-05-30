/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_calc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboeve <jboeve@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:01:20 by jboeve        #+#    #+#                 */
/*   Updated: 2024/05/30 16:30:33 by yesimzaim     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"

t_vec2i	calc_draw_start(t_player *p, t_sprite sp)
{
	t_vec2i	draw_start;

	draw_start.x = -(sp.width) / 2 + sp.screen_x;
	if (draw_start.x < 0)
		draw_start.x = 0;
	draw_start.y = -(sp.height) / 2 + p->meta->image->height / 2;
	if (draw_start.y < 0)
		draw_start.y = 0;
	return (draw_start);
}

t_vec2i	calc_draw_end(t_player *p, t_sprite sp)
{
	t_vec2i	draw_end;

	draw_end.x = sp.width / 2 + sp.screen_x;
	if (draw_end.x >= (int32_t) p->meta->image->width)
		draw_end.x = p->meta->image->width - 1;
	draw_end.y = sp.height / 2 + p->meta->image->height / 2;
	if (draw_end.y >= (int32_t) p->meta->image->height)
		draw_end.y = p->meta->image->height - 1;
	return (draw_end);
}

t_vec2d	calc_transform(t_player *p, t_vec2d pos)
{
	t_vec2d			transform;
	t_vec2d			s_pos;
	double			inv_det;
	const t_vec2d	pp = p->position;
	const t_vec2d	pdir = p->direction;

	s_pos = (t_vec2d){pos.x - pp.x, pos.y - pp.y};
	inv_det = 1.0 / (p->cam_plane.x * pdir.y - pdir.x * p->cam_plane.y);
	transform = (t_vec2d){inv_det * (pdir.y * s_pos.x - pdir.x * s_pos.y), inv_det * (-(p->cam_plane.y) * s_pos.x + p->cam_plane.x * s_pos.y)};
	return (transform);
}
