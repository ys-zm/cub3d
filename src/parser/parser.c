/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                          :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:08:19 by yzaim             #+#    #+#             */
/*   Updated: 2023/11/09 18:52:24 by yzaim            ###   ########.fr       */
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
int map_ext(char *file)
{
	// char str[4] = {'.', 'c', 'u', 'b'};
	const char *str = ".cub";
	int i;
	int j;

	i = 0;
	j = 0;
	
	char *dot = ft_strrchr(file, '.');

	if (dot == file)
		return (EXIT_FAILURE);
	else if (ft_strncmp(dot, str, ft_strlen(dot)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// parse map into 1D array
// index = (y * w) + x (input y and x coordinates to find index pos in array)
int	parser(t_meta *meta, char *map_file)
{
	int fd;
	char *file = NULL;
	char *rect = NULL;
	
	if (map_ext(map_file)) // check map ext
		return(pr_err(INV_EXT), EXIT_FAILURE);
	fd = open(map_file, O_RDONLY); // open file
	if (fd == -1)
		return (pr_err(INV_FILE), EXIT_FAILURE);
	file = read_file(fd);
	if (!file)
		return(pr_err(MALL_ERR));
	if (parse_elements(meta, file))
		return (free(file), EXIT_FAILURE);

	meta->map.width = find_width(meta->map_file); // find largest width
	meta->map.height = find_height(meta->map_file); // find height of map
	// w * h sized rectangle
	rect = make_rect(meta->map_file, meta->map.width, meta->map.height);
	free(meta->map_file);
	if (!rect)
		return(pr_err(MALL_ERR), EXIT_FAILURE);
	if (check_map(meta, rect))
		return (free(rect), EXIT_FAILURE);
	print_map_cell(meta->map.level, meta->map.width, meta->map.height);
	free(rect);
	return (EXIT_SUCCESS);
}
