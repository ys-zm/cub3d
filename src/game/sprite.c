/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   sprite.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/01/25 16:01:20 by jboeve        #+#    #+#                 */
/*   Updated: 2024/01/29 13:00:59 by yesimzaim     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "vector.h"
//#include <algorithm>
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

bool if_black(uint32_t color)
{
	// Extract individual color channels
    uint8_t r = (color >> 24) & 0xFF;
    uint8_t g = (color >> 16) & 0xFF;
    uint8_t b = (color >> 8) & 0xFF;

    // Check if all color channels are 0 (black)
    if (r == 0 && g == 0 && b == 0) {
        return true; // Black
    } else {
        return false; // Not black
    }
}

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

		// loop through every vertical stripe of the sprite on the screen
		int stripe = draw_start.x;
		while (stripe < draw_end.x)
		{
			int tex_x;
			tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * p->meta->attributes.sprites[i].tex->width / sprite_width) / 256;
			if (transform.y > 0 && stripe > 0 && stripe < p->meta->image->width && transform.y < p->z_buffer[stripe])
			{
				int	y;
				y = draw_start.y;
				while (y < draw_end.y)
				{
					int d = (y) * 256 - p->meta->image->height * 128 + sprite_height * 128; //256 and 128 factors to avoid floats
					int tex_y = ((d * p->meta->attributes.sprites[i].tex->height) / sprite_height) / 256;
					uint32_t color = pixel_picker(p->meta->attributes.sprites[i].tex, tex_x, tex_y);
					if (!if_black(color))
					{
						mlx_put_pixel(p->meta->image, stripe, y, color);
					}
					y++;
				}
			}
			stripe++;
		}
		i++;
	}

}
