/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checker.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:42:38 by yzaim         #+#    #+#                 */
/*   Updated: 2024/03/04 15:16:04 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "logging.h"
#include <stdio.h>

/* valid chars : 1, 0, N, S, E, W */
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

/* recursive flood-fill: checks UP/DOWN/LEFT/RIGHT to see moveable areas,
to make sure player is bounded by walls */
int	flood_fill(t_meta *meta, char *map, int x, int y)
{
	int	ret;

	ret = 0;
	if (x < 0 || y < 0 || y >= (int)meta->map.height || \
		x >= (int)meta->map.width)
		return (1);
	if (map[find_index(meta, x, y)] == '1' || \
		map[find_index(meta, x, y)] == '2' || \
		map[find_index(meta, x, y)] == '3')
		return (0);
	if (map[find_index(meta, x, y)] == ' ')
		return (1);
	if (map[find_index(meta, x, y)] == '0')
		map[find_index(meta, x, y)] = '2';
	if (map[find_index(meta, x, y)] == 'D')
		map[find_index(meta, x, y)] = '3';
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

bool	check_valid_doors(t_meta *meta, char *map)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	printf("!!!!\n");
	while (y < meta->map.height)
	{
		x = 0;
		while (x < meta->map.width)
		{
			if (map[find_index(meta, x, y)] == '3')
			{
				printf("found doors\n");
				if (x == 0 || x == meta->map.width - 1 || y == 0 || y == meta->map.height - 1)
					return (false);
				if ((map[find_index(meta, x + 1, y)] != '1' && map[find_index(meta, x - 1, y)] != '1') || \
					(map[find_index(meta, x, y + 1)] != '1' && map[find_index(meta, x, y + 1)] != '1'))
					return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}

int	check_map(t_meta *meta, char *rect)
{
	uint32_t	start_x;
	uint32_t	start_y;

	if (!is_map_chars_valid(rect))
		return (EXIT_FAILURE);
	if (!save_start_pos(meta, rect))
		return (pr_err(NO_PLAYER));
	start_x = meta->map.player_start.x;
	start_y = meta->map.player_start.y;
	rect[find_index(meta, start_x, start_y)] = '0';
	if (flood_fill(meta, rect, start_x, start_y))
		return (pr_err(INV_WALLS));
	if (is_floor_exposed(meta, rect))
		return (pr_err(OUT_OF_BOUNDS));
	if (!check_valid_doors(meta, rect))
	{
		printf("doors need to be next to walls\n");
		return (EXIT_FAILURE);
	}

	if (!save_map(meta, rect))
		return (pr_err(MALL_ERR));
	return (EXIT_SUCCESS);
}
