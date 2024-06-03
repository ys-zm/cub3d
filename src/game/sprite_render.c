/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_render.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboeve <jboeve@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:01:20 by jboeve        #+#    #+#                 */
/*   Updated: 2024/05/30 16:30:48 by yesimzaim     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"

// extracts individual color channels, checks if color channels are 0 (black)
static bool	is_black(uint32_t color)
{
	const uint8_t	r = (color >> 24) & 0xFF;
	const uint8_t	g = (color >> 16) & 0xFF;
	const uint8_t	b = (color >> 8) & 0xFF;

	if (r == 0 && g == 0 && b == 0)
	{
		return (true);
	}
	return (false);
}

static void	draw_pix(t_player *p, t_vec2i tex_pos, t_vec2i index, t_sprite sp)
{
	const uint32_t	color = pixel_picker(sp.tex.tex, tex_pos.x, tex_pos.y);

	if (!is_black(color))
	{
		mlx_put_pixel(p->meta->image, index.x, index.y, color);
	}
}

// loop through every vertical stripe of the sprite on the screen
// d calculation: 256 and 128 factors to avoid floats
void	draw_sprite(t_player *p, t_vec2i draw_start, t_vec2i draw_end, uint32_t i)
{
	const t_sprite	*sp = p->meta->attributes.sprites;
	const t_vec2i	img_dim = {p->meta->image->width, p->meta->image->height};
	t_vec2i			index;
	t_vec2i			tex_pos;
	int				d;

	index.x = draw_start.x;
	while (index.x < draw_end.x)
	{
		tex_pos.x = (int)(256 * (index.x - (-(sp[i].width) / 2 + sp[i].screen_x)) * sp[i].tex.tex->width / sp[i].width) / 256;
		if (sp[i].transform.y > 0 && index.x > 0 && index.x < img_dim.x && sp[i].transform.y < p->z_buffer[index.x])
		{
			index.y = draw_start.y;
			while (index.y < draw_end.y)
			{
				d = (index.y) * 256 - img_dim.y * 128 + sp[i].height * 128;
				tex_pos.y = ((d * sp[i].tex.tex->height) / sp[i].height) / 256;
				draw_pix(p, tex_pos, index, sp[i]);
				index.y++;
			}
		}
		index.x++;
	}
}
