/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:08:19 by yzaim             #+#    #+#             */
/*   Updated: 2023/11/09 18:52:24 by yzaim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"

int valid_char(char c)
{
    return (c == '1' || c == '0' || c == 'N' || c == 'S' \
    || c == 'E' || c == 'W' || c == ' ');
}

int check_pos(char c)
{
    return (c == 'N' || c == 'S' || c == 'E' || c == 'S');
}

// valid chars : 1, 0, N, S, E, W
int check_chars(char *map)
{
    int player;

    player = 0;
    while (*map)
    {
        if (!valid_char(*map))
            return (pr_err(INV_CHAR));
        if (check_pos(*map))
            player++;
        if (player > 1)
            return (pr_err(PLAY_ERR));
        map++;
    }
    return (0);
}

// index = (y * w) + x
int find_index(t_meta *meta, uint32_t y, uint32_t x)
{
    return ((y * meta->map.width) + x);
}

// recursive flood-fill: checks UP/DOWN/LEFT/RIGHT to see moveable areas, to make sure player is bounded by walls
int flood_fill(t_meta *meta, char *map, int x, int y)
{
    int ret;

    ret = 0;
    if (x < 0 || y < 0 || y >= (int)meta->map.height || x >= (int)meta->map.width)
        return (1);
    if (map[find_index(meta, y, x)] == '1' || map[find_index(meta, y, x)] == '2')
        return (0);
    if (map[find_index(meta, y, x)] == ' ')
        return (1);
    if (map[find_index(meta, y, x)] == '0')
        map[find_index(meta, y, x)] = '2';
    ret += flood_fill(meta, map, x + 1, y); // right
    ret += flood_fill(meta, map, x - 1, y); // left
    ret += flood_fill(meta, map, x, y + 1); // up
    ret += flood_fill(meta, map, x, y - 1); // down
    return (ret);
}

void save_start_pos(t_meta *meta, char *map)
{
	int x;
	int y;
    
    y = -1;
	while (++y < (int)meta->map.height)
	{
        x = -1;
		while (++x < (int)meta->map.width)
		{
			if (check_pos(map[find_index(meta, y, x)]))
            {
                meta->player.start_x = x;
                meta->player.start_y = y;
            }
		}
	}
}

// instead of this maybe just crop the map?
int check_other_rooms(t_meta *meta, char *map)
{
	int x;
	int y;
    
    y = -1;
	while (++y < (int)meta->map.height)
	{
        x = -1;
		while (++x < (int)meta->map.width)
		{
            if (map[find_index(meta, y, x)] == '0')
                return (1);
		}
	}
    return (0);
}

int check_map(t_meta *meta, char *rect)
{
    if (check_chars(rect))
		return (1);
    // if (check_horiz_left(meta, rect) || check_horiz_right(meta, rect)) // check all directions
    //     return (1);
    // if (check_vert_top(meta, rect) || check_vert_down(meta, rect))
    //     return (1);
    save_start_pos(meta, rect);
    rect[find_index(meta, meta->player.start_y, meta->player.start_x)] = '0';
    if (flood_fill(meta, rect, meta->player.start_x, meta->player.start_y))
        return (pr_err(INV_WALLS));
    if (check_other_rooms(meta, rect))
        return (pr_err(OUT_OF_BOUNDS));
    return (0);
}