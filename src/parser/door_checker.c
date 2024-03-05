/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   door_checker.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:42:38 by yzaim         #+#    #+#                 */
/*   Updated: 2024/03/05 12:14:24 by yesimzaim     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "logging.h"

static bool	is_valid_dr(t_meta *meta, char *map, uint32_t x, uint32_t y)
{
	bool		valid;

	valid = false;
	if (x == 0 || x == meta->map.width - 1 || \
		y == 0 || y == meta->map.height - 1)
		return (false);
	if ((map[find_index(meta, x + 1, y)] == '1' && \
		map[find_index(meta, x - 1, y)] == '1'))
		valid = true;
	if ((map[find_index(meta, x, y + 1)] == '1' && \
		map[find_index(meta, x, y + 1)] == '1'))
		valid = true;
	return (valid);
}

bool	check_valid_doors(t_meta *meta, char *map)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < meta->map.height)
	{
		x = 0;
		while (x < meta->map.width)
		{
			if (map[find_index(meta, x, y)] == '3' || map[find_index(meta, x, y)] == 'D')
			{
				if (!is_valid_dr(meta, map, x, y))
					return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}
