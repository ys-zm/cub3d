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
		printf("TEX: %s\n", *tex);
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

int check_if_map_line(char *file)
{
	while (*file && *file != '\n')
	{
		if (*file != ' ')
			break ;
		file++;
	}
	if (*file == '\n')
		return (0);
	return (1);
}

int save_map(t_meta *meta, char *file)
{
	int	i;

	while (*file)
	{
		if (check_if_map_line(file))
			break ;
		else
		{
			while (*file && *file != '\n')
				file++;
		}
	}
	printf("HI!\n");
	if (*file)
	{
		i = ft_strlen(file);
		meta->map_file = ft_substr(file, 0, i);
		return (0);
	}
	else
		return (0);
}

int check_file_order(t_meta *meta, char *file)
{ 
	while (*file)
	{
		while (*file && *file == ' ' && *file != '\n')
			file++;
		if (*file == 'N' && save_tex(file, "NO", &(meta->tex->no)))
		{
			printf("NO: %s\n", meta->tex->no);
			while (*file && *file != '\n')
				file++;
		}
		else if (*file == 'S' && save_tex(file, "SO", &(meta->tex->so)))
		{
			printf("SO: %s\n", meta->tex->so);
			while (*file && *file != '\n')
				file++;
		}
		else if (*file == 'W' && save_tex(file, "WE", &(meta->tex->we)))
		{
			printf("WE: %s\n", meta->tex->we);
			while (*file && *file != '\n')
				file++;
		}
		else if (*file == 'E' && save_tex(file, "EA", &(meta->tex->ea)))
		{
			printf("EA: %s\n", meta->tex->ea);
			while (*file && *file != '\n')
				file++;
		}
		if (meta->tex->ea && meta->tex->we && meta->tex->no && meta->tex->so)
			break;
		file++;
	}
	save_map(meta, file);
	printf("map: %s\n", meta->map_file);
	return (0);
}


// parse map into 1D array
// index = (y * w) + x (input y and x coordinates to find index pos in array)
int	parser(t_meta *meta, char *map_file)
{
	int fd;
	char *file = NULL;
	char *rect = NULL;
	
	if (!map_ext(map_file)) // check map ext
		return(pr_err(INV_EXT));
	fd = open(map_file, O_RDONLY); // open file
	if (fd == -1)
		return (pr_err(INV_FILE));
	file = read_file(fd);
	if (!file)
		return(pr_err(MALL_ERR));
	
	printf("file: %s\n", file);

	if (check_file_order(meta, file))
	{
		free(file);
		return (1);
	}
	free(file);
	exit(0);
	// need to separate file first
	meta->map.width = find_width(file); // find largest width
	meta->map.height = find_height(file); // find height of map

	// w * h sized rectangle
	rect = make_rect(file, meta->map.width, meta->map.height);
	if (!rect)
		return(pr_err(MALL_ERR));
	if (check_map(meta, rect))
		return (1);
	
	(void)meta->map;
	free(rect);
	return (0);
}
