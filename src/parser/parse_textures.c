/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_textures.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <yzaim@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:56:45 by yzaim         #+#    #+#                 */
/*   Updated: 2024/03/04 17:05:40 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "logging.h"

bool	valid_colour(char *content)
{
	size_t	commas;

	commas = 0;
	while (*content)
	{
		if (*content == ',')
			commas++;
		if (!ft_isdigit(*content) && *content != ',' && *content != ' ' && *content != '\t')
			return (false);
		content++;
	}
	return (commas == 2);
}

void	free_2d_array(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// saves the RGB values of the F and C elements
bool	get_colour_value(char *content, t_rgba *col)
{
	uint8_t	*ptr;
	char	**arr;
	int32_t	tmp;
	int		i;

	if (!valid_colour(content))
		return (false);
	arr = ft_split(content, ',');
	i = 0;
	ptr = (uint8_t *) col;
	ptr[0] = 255;
	while (i < 3)
	{
		tmp = ft_atoi(arr[i]);
		if (tmp < 0 || tmp > 255)
			return (free_2d_array(arr), false);
		ptr[i + 1] = tmp;
		i++;
	}
	free_2d_array(arr);
	return (true);
}

// mallocs the paths to NO, SO, WE, EA elements
char	*get_tex_val(char *file)
{
	int		i;
	char	*val;

	i = 0;
	skip_spaces(&file);
	while (file[i] && file[i] != '\n')
		i++;
	if (i)
	{
		val = ft_substr(file, 0, i);
		if (!val)
			return (NULL);
		return (val);
	}
	return (ft_strdup(""));
}

// returns true of the characters match those of a valid texture element
bool	is_wall(char *file)
{
	const char	*tx[4] = {"NO", "SO", "WE", "EA"};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (!ft_strcmp_largest(file, tx[i]))
			return (true);
		i++;
	}
	return (false);
}

// returns true of the characters match those of a valid colour element
bool	is_floor_or_ceiling(char *file)
{
	if (*file == 'F')
		return (true);
	if (*file == 'C')
		return (true);
	return (false);
}
