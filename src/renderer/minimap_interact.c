/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   minimap_interact.c                                :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/03/04 17:37:55 by jboeve        #+#    #+#                 */
/*   Updated: 2024/05/29 12:19:34 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render_minimap.h"

void	minimap_zoom(t_minimap *m, t_minimap_zoom dir)
{
	int32_t	tmp;

	if (dir == ZOOM_IN)
	{
		tmp = m->tile_size * MINIMAP_ZOOM_MOD;
		if (tmp > 96)
			tmp = 96;
	}
	else
	{
		tmp = m->tile_size / MINIMAP_ZOOM_MOD;
		if (tmp < 2)
			tmp = 2;
	}
	m->tile_size = (size_t) tmp;
}

void	minimap_init(t_minimap *map)
{
	map->tile_size = MINIMAP_DEFAULT_ZOOM;
}
