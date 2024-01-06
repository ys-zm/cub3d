/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   font_renderer.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/01/05 00:02:23 by joppe         #+#    #+#                 */
/*   Updated: 2024/01/06 02:48:58 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * This file is basically a copy of the `mlx_font.c`
 * but with the ability to add more fonts.
 */

#include "font_vt323_14.h"
#include "meta.h"
#include "font_comicsans.h"
#include "font_dejavu_14.h"
#include "font_vt323_14.h"
#include "font_vt323_19.h"


static int32_t get_texoffset(char c)
{
    const bool _isprint = ft_isprint(c);

	// TODO Use from font atlas
	const int32_t font_w = 12;
    return (-1 * !_isprint + (font_w * (c - 32)) * _isprint);
}

// Literally a copy of `mlx_draw_char` except that ours takes a font to draw.
static void draw_char(mlx_image_t *image, const t_font_atlas *atlas, int32_t font_loc, uint32_t imgoffset)
{
	char*		pixelx;
	uint8_t*	pixeli;

	if (font_loc == -1)
		return;

	for (uint32_t y = 0; y < atlas->font_h; y++)
	{
		// pointer to start of font in atlas.
		pixelx = &atlas->pixels[(y * atlas->width + font_loc) * atlas->bpp];

		// start location in pixels buffer to paste the font
		pixeli = image->pixels + ((y * image->width + imgoffset) * atlas->bpp);

		// Copy row by row, the length is limited by the `cell_w * BPP`
		memcpy(pixeli, pixelx, atlas->font_w * atlas->bpp);
	}
}

const t_font_atlas *cube_get_font_atlas(t_font_family face)
{
	const t_font_atlas *fonts[FONT_COUNT] = {
		[FONT_DEJAVU_14]	=	(t_font_atlas *) &font_dejavu_14,
		[FONT_COMICSANS_14]	=	(t_font_atlas *) &font_comicsans_14,
		[FONT_VT323_14]		=	(t_font_atlas *) &font_vt323_14,
		[FONT_VT323_19]		=	(t_font_atlas *) &font_vt323_19,
	};
	return fonts[face];
}

// TODO If current image is too small resize the it, eg `mlx_resize_image()`
void cube_put_string(mlx_image_t *image, const char *s, const t_font_atlas *atlas, uint32_t x, uint32_t y)
{
	const int32_t len = ft_strlen(s);
	int32_t index;
	int32_t i;

	i = 0;
	while (i < len)
	{
		index = get_texoffset(s[i]);
		uint32_t draw_loc = (y * image->width + (i * atlas->font_w) + x);
		draw_char(image, atlas, index, draw_loc);
		i++;
	}

}
