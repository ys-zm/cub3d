/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   sprite.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/01/25 16:01:20 by jboeve        #+#    #+#                 */
/*   Updated: 2024/01/26 17:22:12 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "vector.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>



// Stub
void init_sprites(t_sprite *sprites)
{
	size_t i = 0;

	while (i < SPRITE_COUNT)
	{
		sprites[i].pos = (t_vec2d){2.5 + (i + 2), 2.5 + (i + 2)};
		i++;
	}
	i = 0;
	sprites[i].tex = mlx_load_png("texture_examples/barrel.png");
	if (!sprites[i].tex)
		UNIMPLEMENTED("mlx_load_png failed");

	i = 1;
	sprites[i].tex = mlx_load_png("texture_examples/pillar.png");
	if (!sprites[i].tex)
		UNIMPLEMENTED("mlx_load_png failed");
}

// static void sprite_sort(int32_t *order, double *dist, uint32_t count)
// {
// 	size_t i = 0;
// 	while (i < count)
// 	{
// 		s[i] =
// 		i++;
// 	}

// }

void sprite_calculate(t_player *p)
{
	size_t i;

	i = 0;
	p->sprite_order[i] = i;
	p->sprite_dist[i] = (7.2);

	i = 1;
	p->sprite_order[i] = i;
	p->sprite_dist[i] = (1.2);


	sprite_sort(p->sprite_dist, p->sprite_order);
	
	i = 0;
	while (i < SPRITE_COUNT)
	{
		const t_sprite *sp = p->meta->attributes.sprites;
		const t_vec2d s_pos	= (t_vec2d){sp[p->sprite_order[i]].pos.x - p->position.x, sp[p->sprite_order[i]].pos.y - p->position.y};


		const double inv_det = 1.0 / (p->cam_plane.x * p->direction.y) - (p->cam_plane.y * p->direction.x);


		const t_vec2d transform = {inv_det * (p->direction.y * s_pos.x - p->direction.x * s_pos.y), 
							inv_det * (-p->cam_plane.y * s_pos.x + p->cam_plane.x * s_pos.y)};
		
		const int32_t sprite_screen_x = (int32_t)(p->meta->image->width / 2) * (1 + transform.x / transform.y);

		// calculate height of the sprite on screen
		const int32_t sprite_height = abs((int)(p->meta->image->height / transform.y));
		t_vec2i draw_start; 
		t_vec2i draw_end; 
		draw_start.y = -sprite_height / 2 + p->meta->image->height / 2;
		if (draw_start.y < 0)
			draw_start.y = 0;
		draw_end.y = sprite_height / 2 + p->meta->image->height / 2;
		if (draw_end.y >= (int32_t) p->meta->image->height)
			draw_end.y = p->meta->image->height - 1;

		const int32_t sprite_width = abs((int)(p->meta->image->height / transform.y));

		// calcaulte the width of the sprite
		draw_start.x = -sprite_width / 2 + sprite_screen_x;
		if (draw_start.x < 0)
			draw_start.x = 0;
		draw_end.x = sprite_width / 2 + sprite_screen_x;
		if (draw_end.x >= (int32_t) p->meta->image->width)
			draw_end.x = p->meta->image->width - 1;


		int stripe = draw_start.x;
		while (stripe < draw_end.x)
		{
				
			stripe++;
		}
	
		i++;
	}

}
