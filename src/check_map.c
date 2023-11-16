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

// returns 1 if walls are not closed
int check_horiz_left(t_meta *meta, char *map)
{
    int closed = 0;
    uint32_t y = -1;
    uint32_t x;

    while (++y < meta->map.height)
    {
        closed = 0;
        x = -1;
        while (++x < meta->map.width)
        {
            // printf("c: %c\n", map[find_index(meta, y, x)]);
            if (map[find_index(meta, y, x)] == '1')
                closed = 1;
            if (!closed && map[find_index(meta, y, x)] == '0') // walls not closed
                return (pr_err(INV_WALLS));
        }
    }
    return (0);
}

// returns 1 if walls are not closed
int check_vert_top(t_meta *meta, char *map)
{
    int closed = 0;
    uint32_t x = -1;
    uint32_t y;

    while (++x < meta->map.width)
    {
        closed = 0;
        y = -1;
        while (++y < meta->map.height)
        {
            if (map[find_index(meta, y, x)] == '1')
                closed = 1;
            if (!closed && map[find_index(meta, y, x)] == '0') // walls not closed
                return (pr_err(INV_WALLS));
        }
    }
    return (0);
}

int check_horiz_right(t_meta *meta, char *map)
{
    int closed = 0;
    uint32_t y = meta->map.height;
    uint32_t x;

    while (--y > 0)
    {
        closed = 0;
        x = meta->map.width;
        while (--x > 0)
        {
            if (map[find_index(meta, y, x)] == '1')
                closed = 1;
            if (!closed && map[find_index(meta, y, x)] == '0') // walls not closed
                return (pr_err(INV_WALLS));
        }
    }
    return (0);
}

int check_vert_down(t_meta *meta, char *map)
{
    int closed = 0;
    uint32_t x = meta->map.width;
    uint32_t y;

    while (--x > 0)
    {
        closed = 0;
        y = meta->map.height;
        while (--y > 0)
        {
            if (map[find_index(meta, y, x)] == '1')
                closed = 1;
            if (!closed && map[find_index(meta, y, x)] == '0') // walls not closed
                return (pr_err(INV_WALLS));
        }
    }
    return (0);
}

int check_map(t_meta *meta, char *rect)
{
    if (check_chars(rect))
		return (1);
    if (check_horiz_left(meta, rect) || check_horiz_right(meta, rect)) // check all directions
        return (1);
    if (check_vert_top(meta, rect) || check_vert_down(meta, rect))
        return (1);
    return (0);
}