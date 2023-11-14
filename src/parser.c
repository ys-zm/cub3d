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

char *check_line(char *l, int w)
{
	int len;
	char *r;
	int i;

	i = 0;
	len = ft_strlen(l);
	if (len < w)
	{
		r = malloc(sizeof(char) * (w - len + 1));
		while (len++ < w)
			r[i++] = ' ';
		r[i] = '\0';
		r = ft_strjoin(l, r);
		free(l);
		return (r);
	}
	return (l);
}

//test this
char *read_file(int fd, int w)
{
	char *line;
	char *full_map;

	line = get_next_line(fd);
	line = check_line(get_next_line(fd), w);
	full_map = NULL;
	while (line)
	{
		full_map = ft_strjoin(full_map, line);
		if (!full_map) // malloc check
		{
			free(line);
			return (NULL);
		}
		free(line);
		line = check_line(get_next_line(fd), w);
	}
	free(line);
	return (full_map);
}

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
	return (h);
}

// check valid map
int check_map(char *map)
{
	//flood_fill algorithm to check if walls are closed
}

int map_ext(char *file)
{
	char str[4] = {'.', 'c', 'u', 'b'};
	int len;
	int i;
	int j;

	len = ft_strlen(file);
	i = len - 5;
	j = 0;
	while (i < len)
	{
		if (file[i++] != str[j++])
			return (0);
	}
	return (1);
}

// not sure of a 1d array will work for misaligned maps
int	parser(t_meta *meta, char *map_file)
{
	int fd;
	char *map;
	
	if (!map_ext(map_file))
		return(print_err("map extension should be .cub\n", 1));
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (print_err("map file failed to open\n", 1));

	meta->map.width = find_width(map);
	meta->map.height = find_height(map);
	printf("width: %u\n", meta->map.width);
	printf("height: %u\n", meta->map.height);

	// width x height to make rectangle
	map = read_file(fd);
	if (!map)
		return(print_err("malloc error reading file\n", 1));

	// flood fill
	(void)meta->map;
	return (0);
}
