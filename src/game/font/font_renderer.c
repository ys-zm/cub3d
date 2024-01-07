/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   font_renderer.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/01/05 00:02:23 by joppe         #+#    #+#                 */
/*   Updated: 2024/01/07 03:28:05 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * This file is basically a copy of the `mlx_font.c`
 * but with the ability to specifiy what font to draw.
 */

#include "MLX42/MLX42_Int.h"
#include "font_dejavu_14.h"
#include "font_comicsans.h"
#include "font_mlx.h"
#include "libft.h"
#include "meta.h"
#include <stdio.h>
#include <string.h>


static int32_t get_texoffset(char c, const t_font_atlas *atlas)
{
    const bool _isprint = ft_isprint(c);

    return (-1 * !_isprint + (atlas->font_w * (c - 32)) * _isprint);
}

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
		[FONT_MLX]			=	(t_font_atlas *) &font_mlx,
		[FONT_DEJAVU_14]	=	(t_font_atlas *) &font_dejavu_14,
		[FONT_COMICSANS_13]	=	(t_font_atlas *) &font_comicsans_13,
	};
	return fonts[face];
}

// TODO If current image is too small resize the it, eg `mlx_resize_image()`
mlx_image_t *cube_put_string(mlx_image_t *image, const char *s, const t_font_atlas *atlas)
{
	int32_t			i;
	const int32_t	len = ft_strlen(s);
	const uint32_t	image_len = len * atlas->font_w;

	if (image_len != image->width)
	{
		ft_bzero(image->pixels, image->width * image->height * BPP);
		if (!mlx_resize_image(image, image_len, atlas->font_h))
			return (NULL);
	}

	i = 0;
	while (i < len)
	{
		draw_char(image, atlas, get_texoffset(s[i], atlas), i * atlas->font_w);
		i++;
	}
	return (image);
}
