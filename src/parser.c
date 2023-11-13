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

char *read_file(int fd)
{
	char *line;
	char *full_map;

	line = get_next_line(fd);
	full_map = NULL;
	while (line)
	{
		full_map = ft_strjoin(full_map, line);
		if (!full_map)
		{
			free(line);
			return (NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (full_map);
}

u_int32_t	find_width(char *map)
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
	return (w);
}

//TODO add a check for a trailing '\n' character
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
	return (h);
}

// not sure if this works
//checking first char on each line is a wall (i.e. left side closed)
int check_left(char *map)
{
	while (*map)
	{
		while (*map && *map == ' ' && *map != '\n')
			map++;
		if (*map != 1) // first char after spaces should be 1 = WALL
			return (0);
		if (*map == 1)
			map++;
		if (*map == ' ')
			return (0);
		while (*map && *map != '\n')
			map++;
		if (*map == '\n')
			map++;
	}
	return (1);
}

// last char should be 1 (can be followed by spaces)
int check_right(char *map)
{
	return (0);
}

//top should be closed off by walls
int check_top(char *map)
{
	return (0);
}

// bottom should be closed off by walls
int check_bottom(char *map)
{
	return (0);
}

// check valid map
// if walls are enclosed: right after nl, right before and first char have to be nl
int check_map(char *map)
{
	if (!check_left(map) || !check_right(map) || !check_top(map) || !check_bottom(map))
		return (0);
	return (1);
}

// not sure of a 1d array will work for misaligned maps
int	parser(t_meta *meta, char *map_file)
{
	int fd;
	char *map;
	
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (print_err("map file failed to open\n", 1));
	map = read_file(fd);
	if (!map)
		return(print_err("malloc error reading file\n", 1));

	meta->map.width = find_width(map);
	meta->map.height = find_height(map);
	printf("width: %u\n", meta->map.width);
	printf("height: %u\n", meta->map.height);
	(void)meta->map;
	return (0);
}
