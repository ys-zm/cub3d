/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                          :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:08:19 by yzaim             #+#    #+#             */
/*   Updated: 2023/12/14 17:22:20 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
# include "test_utils.h"

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

// check if there are characters before .cub and no characters after
int map_extension(char *file)
{
	// char str[4] = {'.', 'c', 'u', 'b'};
	const char *str = ".cub";

	char *dot = ft_strrchr(file, '.');

	if (dot == file)
		return (EXIT_FAILURE);
	else if (ft_strncmp(dot, str, ft_strlen(dot)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	save_map_dimensions(char *map_file, uint32_t *width, uint32_t *height)
{
	*width = find_width(map_file); // find largest width
	*height = find_height(map_file); // find height of map
}

// parse map into 1D array
// index = (y * w) + x (input y and x coordinates to find index pos in array)
int	parser(t_meta *meta, char *map_file)
{
	int fd;
	char *file = NULL;
	char *rect = NULL;
	
	if (map_extension(map_file)) // check map ext
		return(pr_err(INV_EXT), EXIT_FAILURE);
	fd = open(map_file, O_RDONLY); // open file
	if (fd == -1)
		return (pr_err(INV_FILE), EXIT_FAILURE);
	file = read_file(fd);
	if (!file)
		return(pr_err(MALL_ERR));
	if (parse_elements(meta, file))
		return (free(file), EXIT_FAILURE);
	save_map_dimensions(meta->map_file, &meta->map.width, &meta->map.height);
	rect = make_rect(meta->map_file, meta->map.width, meta->map.height);
	print_map(rect, meta->map.width, meta->map.height);
	free(meta->map_file);
	if (!rect)
		return(pr_err(MALL_ERR), EXIT_FAILURE);
	if (check_map(meta, rect))
		return (free(rect), EXIT_FAILURE);
	free(rect);
	return (EXIT_SUCCESS);
}
