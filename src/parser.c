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

// check valid map
// if walls are enclosed: right after nl, right before and first char have to be nl
// 
int check_map(char *map)
{
	char *map;
	
}

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
