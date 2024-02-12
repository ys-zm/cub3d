/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   parser.c                                          :+:    :+:             */
/*+:+ +:+ +:+ */
/*   By: yzaim <marvin@42.fr>   +#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2023/11/09 18:08:19 by yzaim #+##+# */
/*   Updated: 2024/01/29 15:34:19 by yesimzaim     ########   odam.nl         */
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
	rect = make_rect(meta->map.map_element, meta->map.width, meta->map.height);
	// printing map for debugging
	// print_map(rect, meta->map.width, meta->map.height);
	if (!rect)
		return(pr_err(MALL_ERR), EXIT_FAILURE);
	free(meta->map.map_element);
	meta->map.map_element = rect;
	return (EXIT_SUCCESS);
}

bool	out_of_bounds(t_vec2d pos, uint32_t w, uint32_t h)
{
	double	width;
	double	height;

	width = (double)w;
	height = (double)h;
	if (pos.x >= width || pos.y >= height || pos.x <= 0 || pos.y <= 0)
		return (true);
	return (false);

}

int	sprites_coordinates(uint32_t sprite_count, t_sprite *sprites, uint32_t w, uint32_t h)
{
	uint32_t	i;

	i = 0;
	while (i < sprite_count)
	{
		if (out_of_bounds(sprites[i].pos, w, h))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	parser(t_meta *meta)
{
	char	*file = NULL;
	
	save_map_dimensions(meta->map.map_element, &meta->map.width, &meta->map.height);
	create_rectangle_map_element(meta);
	if (check_map(meta, meta->map.map_element))
		return (EXIT_FAILURE);
	if (parse_elements(meta))
		return (EXIT_FAILURE);
	if (sprites_coordinates(meta->attributes.sprite_count, meta->attributes.sprites, meta->map.width, meta->map.height))
		return (pr_err(SP_COORD), EXIT_FAILURE);
	free(meta->map.map_element);
	return (EXIT_SUCCESS);
}
