/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checker.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:42:38 by yzaim         #+#    #+#                 */
/*   Updated: 2024/02/14 13:02:36 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

// valid chars : 1, 0, N, S, E, W
bool	is_map_chars_valid(char *map)
{
	uint32_t	player;

	player = 0;
	while (*map)
	{
		if (!valid_map_char(*map))
			return (pr_err(INV_CHAR), false);
		if (player_pos_char(*map))
			player++;
		if (player > 1)
			return (pr_err(PLAY_ERR), false);
		map++;
	}
	return (true);
}

// recursive flood-fill: checks UP/DOWN/LEFT/RIGHT to see moveable areas, 
// to make sure player is bounded by walls
int	flood_fill(t_meta *meta, char *map, int x, int y)
{
	int	ret;

	ret = 0;
	if (x < 0 || y < 0 || y >= (int)meta->map.height || x >= (int)meta->map.width)
		return (1);
	if (map[find_index(meta, x, y)] == '1' || map[find_index(meta, x, y)] == '2')
		return (0);
	if (map[find_index(meta, x, y)] == ' ')
		return (1);
	if (map[find_index(meta, x, y)] == '0')
		map[find_index(meta, x, y)] = '2';
	ret += flood_fill(meta, map, x + 1, y);
	ret += flood_fill(meta, map, x - 1, y);
	ret += flood_fill(meta, map, x, y + 1);
	ret += flood_fill(meta, map, x, y - 1);
	return (ret);
}

bool	save_start_pos(t_meta *meta, char *map)
{
	uint32_t	x;
	uint32_t	y;
	bool		found;

	found = false;
	y = 0;
	while (y < meta->map.height)
	{
		x = 0;
		while (x < meta->map.width)
		{
			if (player_pos_char(map[find_index(meta, x, y)]))
			{
				meta->map.player_start.x = x;
				meta->map.player_start.y = y;
				meta->map.player_start_dir = map[find_index(meta, x, y)];
				found = true;
			}
			x++;
		}
		y++;
	}
	return (found);
}

// TODO instead of this maybe just crop the map?
bool	is_floor_exposed(t_meta *meta, char *map)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < meta->map.height)
	{
		x = 0;
		while (x < meta->map.width)
		{
			if (map[find_index(meta, x, y)] == '0')
				return (true);
			x++;
		}
		y++;
	}
	return (false);
}

int	check_map(t_meta *meta, char *rect)
{
	if (!is_map_chars_valid(rect))
		return (EXIT_FAILURE);
	if (!save_start_pos(meta, rect))
		return (pr_err(NO_PLAYER));
	rect[find_index(meta, meta->map.player_start.x, meta->map.player_start.y)] = '0';
	if (flood_fill(meta, rect, meta->map.player_start.x, meta->map.player_start.y))
		return (pr_err(INV_WALLS));
	if (is_floor_exposed(meta, rect)) // maybe change to a warning?
		return (pr_err(OUT_OF_BOUNDS));
	if (!save_map(meta, rect))
		return (pr_err(MALL_ERR));
	return (EXIT_SUCCESS);
}
