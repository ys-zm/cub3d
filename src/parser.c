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
		full_map = ft_strjoin_free(full_map, line);
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

// check if there are characters before .cub and no characters after
int map_ext(char *file)
{
	char str[4] = {'.', 'c', 'u', 'b'};
	int i;
	int j;

	i = 0;
	j = 0;
	while (file[i] && file[i] != '.')
		i++;
	if (!i)
		return (1);
	while (file[i] && file[i] == str[j])
		i++;
	if (file[i])
		return (1);
	return (0);
}

// returns 1 if texture matches and if able to save textuer
int save_tex(char *file, char *cmp, char **tex)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (*file && cmp[i] && *file != '\n')
	{
		if (*file != cmp[i])
			break;
		i++;
		file++;
	}
	if (i == 2)
	{
		while (*file && *file == ' ' && *file != '\n')
			file++;
		while (file[j] && file[j] != '\n')
			j++;
		*tex = ft_substr(file, 0, j);
		if (!tex)
			return (0);
		return (1);
	}
	else
	{
		*tex = ft_strdup(NULL);
	}
	return (0);
}

// parse map into 1D array
// index = (y * w) + x (input y and x coordinates to find index pos in array)
int	parser(t_meta *meta, char *map_file)
{
	int fd;
	char *file = NULL;
	char *rect = NULL;
	
	if (map_ext(map_file)) // check map ext
		return(pr_err(INV_EXT));
	fd = open(map_file, O_RDONLY); // open file
	if (fd == -1)
		return (pr_err(INV_FILE));
	file = read_file(fd);
	if (!file)
		return(pr_err(MALL_ERR));
	if (parse_textures(meta, file))
		return (free(file), 1);
	free(file);
	meta->map.width = find_width(meta->map_file); // find largest width
	meta->map.height = find_height(meta->map_file); // find height of map
	// w * h sized rectangle
	rect = make_rect(meta->map_file, meta->map.width, meta->map.height);
	if (!rect)
		return(free(meta->map_file), pr_err(MALL_ERR));
	free(meta->map_file);
	if (check_map(meta, rect))
		return (free(rect), 1);
	free(rect);
	return (0);
}
