/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parser.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:30:18 by yzaim         #+#    #+#                 */
/*   Updated: 2024/03/04 15:16:04 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "logging.h"

t_cell_type	find_enum_value(char c)
{
	if (c == ' ')
	{
		return (MAP_EMPTY);
	}
	else if (c == '1')
	{
		return (MAP_WALL);
	}
	else if (c == '3')
		return (MAP_DOOR_CLOSED);
	else
	{
		return (MAP_SPACE);
	}
}

bool	save_map(t_meta *meta, char *rect)
{
	uint32_t	i;
	size_t		size;

	size = meta->map.width * meta->map.height;
	meta->map.level = malloc(sizeof(t_cell_type) * size);
	if (!meta->map.level)
		return (false);
	i = 0;
	while (rect[i])
	{
		meta->map.level[i] = find_enum_value(rect[i]);
		i++;
	}
	return (true);
}
