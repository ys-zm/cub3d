/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   parser.c                                          :+:    :+:             */
/*+:+ +:+ +:+ */
/*   By: yzaim <marvin@42.fr>   +#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2023/11/09 18:08:19 by yzaim #+##+# */
/*   Updated: 2024/03/03 19:02:45 by joppe         ########   odam.nl         */
/**/
/* ************************************************************************** */

#include "error.h"

bool	out_of_bounds(t_vec2d pos, uint32_t w, uint32_t h)
{
	double	width;
	double	height;

	width = (double)w;
	height = (double)h;
	if (pos.x >= width || pos.y >= height || pos.x <= 0 || pos.y <= 0)
	{
		printf("posx: %f | posy: %f\n", pos.x, pos.y);
		return (true);
	}
	return (false);
}

int	sprites_coordinates(uint32_t sprite_count, \
		t_sprite *sprites, uint32_t w, uint32_t h)
{
	uint32_t	i;

	i = 0;
	while (i < sprite_count)
	{
		if (out_of_bounds(sprites[i].pos, w, h))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	parser(t_meta *meta)
{
	save_map_dimensions(meta->map.map_element, \
			&meta->map.width, &meta->map.height);
	create_rectangle_map_element(meta);
	if (check_map(meta, meta->map.map_element))
		return (EXIT_FAILURE);
	if (parse_elements(meta))
		return (EXIT_FAILURE);
	if (sprites_coordinates(meta->attributes.sprite_count, \
			meta->attributes.sprites, meta->map.width, meta->map.height))
		return (pr_err(SP_COORD), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
