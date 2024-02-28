/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_access_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:30:18 by yzaim         #+#    #+#                 */
/*   Updated: 2024/02/14 17:52:10 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "error.h"

uint32_t	find_width(char *map)
{
	uint32_t	w;
	uint32_t	count;

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
	return (w);
}

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
			continue ;
		}
		map++;
	}
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
		while (*map && *map != '\n')
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
int	find_index(t_meta *meta, uint32_t x, uint32_t y)
{
	return ((y * meta->map.width) + x);
}

bool	is_path(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '/')
			return (true);
		i++;
	}
	return (false);
}
