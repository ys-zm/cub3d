/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:26:06 by yzaim         #+#    #+#                 */
/*   Updated: 2024/02/14 12:59:23 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_map_line(char *file)
{
	while (*file && *file != '\n')
	{
		if (*file != ' ')
			break ;
		file++;
	}
	if (*file == '\n')
		return (false);
	return (true);
}

// check if there are characters before .cub and no characters after
int	map_extension(char *file)
{
	const char	*str = ".cub";
	uint32_t	compare_len;
	char		*dot;

	dot = ft_strrchr(file, '.');
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
	*width = find_width(map_file);
	*height = find_height(map_file);
}

int	create_rectangle_map_element(t_meta *meta)
{
	char	*rect;

	rect = NULL;
	rect = make_rect(meta->map.map_element, meta->map.width, meta->map.height);
	if (!rect)
		return (pr_err(MALL_ERR), EXIT_FAILURE);
	free(meta->map.map_element);
	meta->map.map_element = rect;
	return (EXIT_SUCCESS);
}

char	*file_to_string(int fd)
{
	char	*line;
	char	*full_map;

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
