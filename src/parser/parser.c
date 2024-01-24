/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   parser.c                                          :+:    :+:             */
/*+:+ +:+ +:+ */
/*   By: yzaim <marvin@42.fr>   +#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2023/11/09 18:08:19 by yzaim #+##+# */
/*   Updated: 2024/01/18 10:45:18 by jboeve        ########   odam.nl         */
/**/
/* ************************************************************************** */

#include "parser.h"
#include "test_utils.h"

	char	*file_to_string(int fd)
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
	const char	*str = ".cub";
	uint32_t	compare_len;

	char *dot = ft_strrchr(file, '.');
	if (dot == file || !dot)
		return (EXIT_FAILURE);
	compare_len = ft_strlen(dot);
	if (compare_len < 4)
		compare_len = 4;
	if (ft_strncmp(dot, str, compare_len))
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

char *parse_file(char *map_file)
{
	int	fd;
	char *file = NULL;
	if (map_extension(map_file)) // check map ext
		return(pr_err(INV_EXT), NULL);
	fd = open(map_file, O_RDONLY); // open file
	if (fd == -1)
		return (pr_err(INV_FILE), NULL);
	file = file_to_string(fd);
	close(fd);
	if (!file)
		return(pr_err(MALL_ERR), NULL);
	return (file);
}

int	create_rectangle_map_element(t_meta *meta)
{
	char	*rect = NULL;
	rect = make_rect(meta->map_element, meta->map.width, meta->map.height);
	// printing map for debugging
	// print_map(rect, meta->map.width, meta->map.height);
	if (!rect)
		return(pr_err(MALL_ERR), EXIT_FAILURE);
	free(meta->map_element);
	meta->map_element = rect;
	return (EXIT_SUCCESS);
}

// should i put a minimun on the width and height
// TODO: Add parser for floor and ceiling texture path
int	parser(t_meta *meta, char *map_file)
{
	char	*file = NULL;
	
	meta->scene_name = map_file;
	file = parse_file(map_file);
	if (!file)
		return(EXIT_FAILURE);
	if (parse_elements(meta, file))
		return (EXIT_FAILURE);
	save_map_dimensions(meta->map_element, &meta->map.width, &meta->map.height);
	create_rectangle_map_element(meta);
	if (check_map(meta, meta->map_element))
		return (EXIT_FAILURE);
	free(meta->map_element);
	return (EXIT_SUCCESS);
}
