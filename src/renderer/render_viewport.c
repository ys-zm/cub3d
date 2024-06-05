/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_viewport.c                                 :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:28:08 by yzaim         #+#    #+#                 */
/*   Updated: 2024/06/05 13:36:41 by yesimzaim     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include <stdint.h>
#include <sys/_types/_u_int32_t.h>

void	render_fc(mlx_image_t *image, t_player *p)
{
	uint32_t	col;
	uint32_t	row;

	col = 0;
	row = 0;
	if (p->should_render)
	{
		while (row < image->height)
		{
			col = 0;
			while (col < image->width)
			{
				draw_floor(p->meta->image, &p->vrays[row], &p->meta->attributes, (t_vec2i){row, col});
				draw_ceil(p->meta->image, &p->vrays[row], &p->meta->attributes, (t_vec2i){row, col});
				p->vrays[row].floor = vec2d_add(p->vrays[row].floor, p->vrays[row].step);
				col++;
			}
			row++;
		}
		p->should_render = false;
	}
}

// render walls
void	render_walls(mlx_image_t *image, t_player *p)
{
	uint32_t	col;

	col = 0;
	while (col < image->width)
	{
		draw_column(p->meta, &p->hrays[col], col, image->height);
		col++;
	}
}

void	render_viewport(mlx_image_t *image, t_player *p)
{
	const int32_t	crosshair_size = 8;

	render_fc(image, p);
	render_walls(image, p);
	dither_img(image);
	//halftone_img(image);
	//draw_rect(image, (t_vec2u){(WINDOW_WIDTH / 2 - (crosshair_size / 2)), (WINDOW_HEIGHT / 2 - (crosshair_size / 2))}, (t_vec2u){crosshair_size, crosshair_size}, 0xFFFFFFFF);
}
