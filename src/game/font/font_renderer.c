/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_renderer.c                                   :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:26:51 by yzaim             #+#    #+#             */
/*   Updated: 2024/02/23 23:20:22 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * This file is basically a copy of the `mlx_font.c`
 * but with the ability to specifiy what font to draw.
 */

#include "font_dejavu_14.h"
#include "font_comicsans.h"
#include "font_mlx.h"
#include "meta.h"
#include <stdint.h>

static int32_t	get_texoffset(char c, const t_font_atlas *atlas)
{
	const bool	_isprint = ft_isprint(c);

	return (-1 * !_isprint + (atlas->font_w * (c - 32)) * _isprint);
}

static void	draw_char(mlx_image_t *image, const t_font_atlas *atlas, \
						int32_t font_loc, uint32_t imgoffset)
{
	char		*pixelx;
	uint8_t		*pixeli;
	uint32_t	y;

	if (font_loc == -1)
		return ;
	y = 0;
	while (y < atlas->font_h)
	{
		pixelx = &atlas->pixels[(y * atlas->width + font_loc) * atlas->bpp];
		pixeli = image->pixels + ((y * image->width + imgoffset) * atlas->bpp);
		memcpy(pixeli, pixelx, atlas->font_w * atlas->bpp);
		y++;
	}
}

const t_font_atlas	*cube_get_font_atlas(t_font_family face)
{
	const t_font_atlas	*fonts[FONT_COUNT] = {
	[FONT_MLX] = (t_font_atlas *) &font_mlx,
	[FONT_DEJAVU_14] = (t_font_atlas *) &font_dejavu_14,
	[FONT_COMICSANS_13] = (t_font_atlas *) &font_comicsans_13,
	};

	return (fonts[face]);
}

// TODO If current image is too small resize the it, eg `mlx_resize_image()`
mlx_image_t	*cube_put_string(mlx_image_t *image, const char *s, \
								const t_font_atlas *atlas)
{
	int32_t			i;
	const int32_t	len = ft_strlen(s);
	const uint32_t	image_w = len * atlas->font_w;

	if (image_w != image->width)
	{
		ft_bzero(image->pixels, image->width * image->height * sizeof(int32_t));
		if (!mlx_resize_image(image, image_w, atlas->font_h))
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
