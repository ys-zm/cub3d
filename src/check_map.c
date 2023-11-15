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

