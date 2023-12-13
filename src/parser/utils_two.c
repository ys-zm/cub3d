/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                       :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:08:19 by yzaim             #+#    #+#             */
/*   Updated: 2023/12/13 16:41:33 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include <stdint.h>

// func to find longest width in map
uint32_t	find_width(char *map)
{
	uint32_t w;
	uint32_t count;

	w = 0;
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
	printf("w: %u\n", w);
	return (w);
}

//TODO add a check for a trailing '\n' character?
uint32_t	find_height(char *map)
{
	uint32_t	h;

	h = 1;
	while (*map)
	{
		if (*map == '\n')
		{
			map++;
			if (*map && *map != '\n')
			{
				h++;
			}
			continue;
		}
		map++;
	}
	// h += 1;
	printf("h: %u\n", h);
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
int find_index(t_meta *meta, uint32_t x, uint32_t y)
{
    return ((y * meta->map.width) + x);
}
