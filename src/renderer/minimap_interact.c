/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   minimap_interact.c                                :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/03/04 17:37:55 by jboeve        #+#    #+#                 */
/*   Updated: 2024/03/04 17:38:18 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render_minimap.h"

void minimap_zoom(t_minimap *m, t_minimap_zoom dir)
{
	size_t	tmp;

	if (dir == ZOOM_IN)
	{
		tmp = m->tile_size;
		m->tile_size *= MINIMAP_ZOOM_MOD;
		if (m->tile_size < tmp)
			m->tile_size = tmp;
	}
	else
	{
		tmp = m->tile_size;
		m->tile_size /= MINIMAP_ZOOM_MOD;
		if (m->tile_size > tmp)
			m->tile_size = tmp;
	}
		
}

void minimap_init(t_minimap *map)
{
	map->tile_size = MINIMAP_DEFAULT_ZOOM;
}
