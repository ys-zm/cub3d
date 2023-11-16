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

char	*read_file(int fd)
{
	char *line;
	char *full_map;

	line = get_next_line(fd);
	full_map = NULL;
	while (line)
	{
		full_map = ft_strjoin(full_map, line);
		if (!full_map)
			return (NULL);
		line = get_next_line(fd);
	}
	return (full_map);
}

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
	printf("w: %u\n", w);
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
	printf("h: %u\n", h);
	return (h);
}


int map_ext(char *file)
{
	char str[4] = {'.', 'c', 'u', 'b'};
	int len;
	int i;
	int j;

	len = ft_strlen(file);
	i = len - 4;
	j = 0;
	while (i < len)
	{
		if (file[i++] != str[j++])
			return (0);
	}
	printf("map file is ok\n");
	return (1);
}

// parse map into 1D array
// index = (y * w) + x (input y and x coordinates to find index pos in array)
int	parser(t_meta *meta, char *map_file)
{
	int fd;
	char *map = NULL;
	char *rect = NULL;
	
	if (!map_ext(map_file)) // check map ext
		return(pr_err(INV_EXT));
	fd = open(map_file, O_RDONLY); // open file
	if (fd == -1)
		return (pr_err(INV_FILE));
	map = read_file(fd);
	if (!map)
		return(pr_err(MALL_ERR));
	meta->map.width = find_width(map); // find largest width
	meta->map.height = find_height(map); // find height of map

	// w * h sized rectangle
	rect = make_rect(map, meta->map.width, meta->map.height);
	if (!rect)
		return(pr_err(MALL_ERR));
	printf("%s\n", rect);
	if (check_map(meta, rect))
		return (1);
	// flood fill
	(void)meta->map;
	free(rect);
	free(map);
	return (0);
}
