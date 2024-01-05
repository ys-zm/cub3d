/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   font_renderer.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/01/05 00:02:23 by joppe         #+#    #+#                 */
/*   Updated: 2024/01/05 01:09:49 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * This file is basically a copy of the `mlx_font.c`
 * but with the ability to add more fonts.
 */

#include "meta.h"
#include "font.h"

// Bytes per pixel, same value as MLX uses for its pixel arrays.
#define BPP 4

static int32_t get_texoffset(char c)
{
    const bool _isprint = ft_isprint(c);

	const int32_t font_w = 16;
    return (-1 * !_isprint + (font_w * c) * _isprint);
}

typedef struct
{
	unsigned int 	 width;
	unsigned int 	 height;
	unsigned int 	 font_w;
	unsigned int 	 font_h;
	unsigned int 	 bpp;
	char	 *pixels;
}T;



static void draw_char(mlx_image_t *image, T *atlas, int32_t font_loc, uint32_t imgoffset)
{
	if (font_loc == -1)
		return;
	char* pixelx;
	uint8_t* pixeli;
	uint32_t cell_h = atlas->font_h;
	uint32_t cell_w = atlas->font_w;
	for (uint32_t y = 0; y < cell_h; y++)
	{
		// pointer at start of font in atlas.
		uint32_t index = (y * atlas->width + font_loc);
		if (index >= atlas->width * atlas->height)
			return;
		pixelx = &atlas->pixels[index * BPP];
		// start location in pixels buffer to paste the font
		pixeli = image->pixels + ((y * image->width + imgoffset) * BPP);
		// Copy row by row, the length is limited by the `cell_w * BPP`
		memcpy(pixeli, pixelx, cell_w * BPP);
	}
}


void cube_put_string(mlx_image_t *image, const char *s, uint32_t x, uint32_t y)
{
	const int32_t font_w = 16;
	int32_t len = ft_strlen(s);
	int32_t index;
	int32_t i = 0;


	T *font_atlas = &cube_font_atlas;


	while (i < len)
	{
		index = get_texoffset(s[i]);
		uint32_t draw_loc = (y * image->width + (i * font_w) + x);
		draw_char(image, font_atlas, index, draw_loc);
		i++;
	}

}
