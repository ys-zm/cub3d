/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboeve <jboeve@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:01:20 by jboeve        #+#    #+#                 */
/*   Updated: 2024/02/14 12:23:01 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "vector.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include "error.h"

// Stub
int	init_sprites(uint32_t count, int32_t **sprite_order, double **sprite_dist)
{
	*sprite_order = malloc(sizeof(int32_t) * count);
	if (!*sprite_order)
		return (pr_err(MALL_ERR), EXIT_FAILURE);
	*sprite_dist = malloc(sizeof(double) * count);
	if (!*sprite_dist)
		return (pr_err(MALL_ERR), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	fill_up_arr(t_player *p)
{
	size_t	i;
	t_vec2d	sp_pos;
	t_vec2d	pp;

	i = 0;
	pp = p->position;
	while (i < p->meta->attributes.sprite_count)
	{
		p->sprite_order[i] = i;
		sp_pos = p->meta->attributes.sprites[i].pos;
		p->sprite_dist[i] = ((pp.x - sp_pos.x) * (pp.x - sp_pos.x)) \
							+ ((pp.y - sp_pos.y) * (pp.y - sp_pos.y));
		i++;
	}
}

void	sprite_calculate(t_player *p)
{
	size_t		i;
	int32_t		ind;
	t_sprite	*sp;
	t_vec2i		draw_start;
	t_vec2i		draw_end;

	fill_up_arr(p);
	sprite_sort(p->sprite_dist, p->sprite_order, \
				p->meta->attributes.sprite_count);
	i = 0;
	while (i < p->meta->attributes.sprite_count)
	{
		sp = p->meta->attributes.sprites;
		ind = p->sprite_order[i];
		sp[ind].transform = calc_transform(p, sp[ind].pos);
		sp[ind].screen_x = (int32_t)(p->meta->image->width / 2) * \
							(1 + sp[ind].transform.x / sp[ind].transform.y);
		sp[ind].height = abs((int)(p->meta->image->height \
								/ sp[ind].transform.y));
		sp[ind].width = abs((int)(p->meta->image->height \
								/ sp[ind].transform.y));
		draw_start = calc_draw_start(p, sp[ind]);
		draw_end = calc_draw_end(p, sp[ind]);
		draw_sprite(p, draw_start, draw_end, ind);
		i++;
	}
}
