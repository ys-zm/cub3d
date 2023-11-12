/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   map.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/12 16:49:44 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/12 20:14:09 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "meta.h"
#include <stdint.h>
#include <stdio.h>



static t_vec2i	map_pos_to_index(t_vec2f pos)
{
	const t_vec2i	player_pos = vec2f_to_vec2i(pos);
	return ((t_vec2i){player_pos[VEC_X] / CELL_WIDTH, player_pos[VEC_Y] / CELL_HEIGHT});
}

t_cell_type	map_get_cell_type(t_map *m, t_vec2f pos)
{
	t_vec2i map_index = map_pos_to_index(pos);
	size_t index = (map_index[VEC_Y] * m->width) + map_index[VEC_X];
	if (index > m->width * m->height)
	{
		printf("index [%ld]\n", index);
		UNIMPLEMENTED("Array out of bounds!");
	}
	return (m->level[index]);
}
