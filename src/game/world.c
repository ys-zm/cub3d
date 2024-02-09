/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   world.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/02/09 14:47:27 by joppe         #+#    #+#                 */
/*   Updated: 2024/02/09 16:13:33 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// return if tile your looking at is a door.
#include "meta.h"
#include "vector.h"
#include "parser.h"

void world_is_door(t_ray r)
{
	
}

void world_door_toggle(t_map *m, t_cell_type cell, size_t index)
{
	if (cell == MAP_DOOR_CLOSED)
		m->level[index] = MAP_DOOR_OPEN;
	else
		m->level[index] = MAP_DOOR_CLOSED;
}

void world_interact(t_player *p, t_vec2d map_pos)
{
	const size_t index = find_index(p->meta, map_pos.y, map_pos.y);
	const t_cell_type cell = p->meta->map.level[index];
	world_door_toggle(&p->meta->map, cell, index);
}

bool world_is_interactable(t_cell_type cell)
{
	return (cell == MAP_DOOR_CLOSED || cell == MAP_DOOR_OPEN);
}
