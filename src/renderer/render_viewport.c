/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_viewport.c                                 :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:28:08 by yzaim         #+#    #+#                 */
/*   Updated: 2024/06/05 00:29:17 by yesimzaim     ########   odam.nl         */
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

static uint32_t idx(uint32_t x, uint32_t y, uint32_t w)
{
	return ((y * w + x) * 4);
}

// Ditherig effect Floyd-Steinberg dithering
// Looping over the image horizontally i.e. y loop first makes a different
mlx_image_t	*dither_img(mlx_image_t *image)
{

	for (uint32_t y = 0; y < image->height - 1; y++)
	{
		for (uint32_t x = 1; x < image->width - 1; x++)
		{
			uint32_t index = idx(x, y, image->width); // Find index relevant in image array storing pixel color info
			uint8_t r = image->pixels[index];
			uint8_t g = image->pixels[index + 1];
			uint8_t b = image->pixels[index + 2];

			int fc = 2;
			uint8_t new_r = round(fc * r / 255) * 255/fc; 
			uint8_t new_g = round(fc * g / 255) * 255/fc;
			uint8_t new_b = round(fc * b / 255) * 255/fc;
			// int8_t new_g = round(((2 * g>>8)) * ((255>>1)));
			// uint8_t new_b = round(((2 * b>>8)) * ((255>>1)));
			// uint8_t new_r = round(((2 * r>>8)) * ((255>>1)));
			
			int32_t err_r = r - new_r;
			int32_t err_g = g - new_g;
			int32_t err_b = b - new_b;

			image->pixels[index] = new_r;
            image->pixels[index + 1] = new_g;
            image->pixels[index + 2] = new_b;

            // Distribute the quantization error to 4 neightbouring pixels in 7/16, 1/16, 3/16, 5/16 ratio
			uint32_t pix1 = idx(x + 1, y, image->width);
            image->pixels[pix1] += err_r * 7 / 16.0;
            image->pixels[pix1 + 1] += err_g * 7 / 16.0;
            image->pixels[pix1 + 2] += err_b * 7 / 16.0;

			uint32_t pix2 = idx(x - 1, y + 1, image->width);
            image->pixels[pix2] += err_r * 3 / 16.0;
            image->pixels[pix2 + 1] += err_g * 3 / 16.0;
            image->pixels[pix2 + 2] += err_b * 3 / 16.0;

			uint32_t pix3 = idx(x, y + 1, image->width);
			image->pixels[pix3] += err_r * 5 / 16.0;
            image->pixels[pix3 + 1] += err_g * 5 / 16.0;
            image->pixels[pix3 + 2] += err_b * 5 / 16.0;

			uint32_t pix4 = idx(x + 1, y + 1, image->width);
            image->pixels[pix4] += err_r * 1 / 16.0;
            image->pixels[pix4 + 1] += err_g * 1 / 16.0;
            image->pixels[pix4 + 2] += err_b * 1 / 16.0;
        }
	}
    return (image);
}

void	render_viewport(mlx_image_t *image, t_player *p)
{
	const int32_t	crosshair_size = 8;

	render_fc(image, p);
	render_walls(image, p);
	image = dither_img(image);	
	//draw_rect(image, (t_vec2u){(WINDOW_WIDTH / 2 - (crosshair_size / 2)), (WINDOW_HEIGHT / 2 - (crosshair_size / 2))}, (t_vec2u){crosshair_size, crosshair_size}, 0xFFFFFFFF);
	
}
