/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_textures.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <yzaim@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:56:45 by yzaim         #+#    #+#                 */
/*   Updated: 2024/01/24 11:02:13 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// saves the RGB values of the F and C elements
// check if RGB is correct?
void	get_colour_value(char *content, t_rgba *col)
{
	col->r = ft_atoi(content);
	while (*content && *content != ',')
		content++;
	if (*content == ',')
		content++;
	col->g = ft_atoi(content);
	while (*content && *content != ',')
		content++;
	if (*content == ',')
		content++;
	col->b = ft_atoi(content);
	col->a = 255;
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
	char	*tx[4] = {"NO", "SO", "WE", "EA"};
	int		i;

	i = 0;
	while (i < 4)
	{
		if (!ft_strncmp(file, tx[i], 2))
			return (true);
		i++;
	}
	return (false);
}

// returns true of the characters match those of a valid colour element
bool is_floor_or_ceiling(char *file)
{
	if (*file == 'F')
		return (true);
	if (*file == 'C')
		return (true);
	return (false);
}
