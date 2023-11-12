/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   map.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/12 16:49:44 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/12 19:00:22 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "meta.h"
#include <stdio.h>



t_vec2i	map_get_cell_location(t_map *m, t_vec2f pos)
{

}

t_cell_type	map_get_cell_type(t_map *m, t_vec2i pos)
{
	size_t index = (pos[VEC_Y] / CELL_HEIGHT * m->width) + pos[VEC_X] /CELL_WIDTH;
	if (index < 0 || index > m->width * m->height)
	{
		printf("index [%ld]\n", index);
		UNIMPLEMENTED("Array out of bounds!");
	}
	return (m->level[index]);
}
