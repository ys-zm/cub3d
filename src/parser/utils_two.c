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

// func to find longest width in map
uint32_t	find_width(char *map)
{
	int w;
	int count;

	w = -1;
	while (*map)
	{
		count = 0;
		while (*map && *map != '\n')
		{
			count++;
			map++;
		}
		if (*map == '\n')
			map++;
		if (w < count)
			w = count;
	}
	// printf("w: %u\n", w);
	return (w);
}

//TODO add a check for a trailing '\n' character?
uint32_t	find_height(char *map)
{
	uint32_t	h;

	h = 0;
	while (*map)
	{
		if (*map == '\n')
			h++;
		map++;
	}
	h += 1;
	// printf("h: %u\n", h);
	return (h);
}

char	*make_rect(char *map, uint32_t w, uint32_t h)
{
	char		*r;
	int			i;
	uint32_t	lc;

	lc = 0;
	i = 0;
	r = malloc(sizeof(char) * (w * h) + h + 1);
	if (!r)
		return (NULL);
	while (*map)
	{
		lc = 0;
		while(*map && *map != '\n')
		{
			r[i++] = *map;
			lc++;
			map++;
		}
		while (lc++ < w)
			r[i++] = ' ';
		if (*map == '\n')
			map++;
	}
	r[i] = 0;
	return (r);
}

// index = (y * w) + x
int find_index(t_meta *meta, uint32_t y, uint32_t x)
{
    return ((y * meta->map.width) + x);
}