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
    if (c == '1' || c == '0')
        return (1);
    
}

// valid chars : 1, 0, N, S, E, W
int check_chars(char *map)
{
    int player;

    player = 0;
    while (*map)
    {
        if (!valid_char(*map))
            return (1);
        map++;
    }
    return (0);
}