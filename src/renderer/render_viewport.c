/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_viewport.c                                 :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:28:08 by yzaim         #+#    #+#                 */
/*   Updated: 2024/05/30 21:27:44 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "meta.h"
#include <stdio.h>

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

// TODO remove unused function?
static uint32_t	index_at(uint32_t x, uint32_t y, uint32_t width, uint8_t bpp)
{
	int index = (x + y * width) * bpp; //Looping over every pixel;
	return (index);
}


void print_tex(mlx_texture_t *texture, mlx_image_t *image)
{
	const int center_x = (image->width / 2 + (texture->width / 2));
	const int center_y = (image->height / 2 + (texture->height / 2));

	for (size_t x = 0; x < texture->width; x++) 
	{
		for (size_t y = 0; y < texture->height; y++) 
		{
			// mlx_put_pixel(image, x, y, texture->pixels[(x * image->width) + y]);
			uint32_t c = pixel_picker(texture, x, y);
			mlx_put_pixel(image, x + center_x, y + center_y, c);
		}
	}

}


void	render_viewport(mlx_image_t *image, t_player *p)
{
	const int32_t	crosshair_size = 8;

	render_fc(image, p);
	render_walls(image, p);
	draw_rect(image, (t_vec2u){(WINDOW_WIDTH / 2 - (crosshair_size / 2)), (WINDOW_HEIGHT / 2 - (crosshair_size / 2))}, (t_vec2u){crosshair_size, crosshair_size}, 0xFFFFFFFF);
	sprite_calculate(p);

	mlx_texture_t	*texture = (p->meta->attributes.n.tex);
	// print_tex(texture, image);
}
