/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_textures.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <yzaim@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:56:45 by yzaim         #+#    #+#                 */
/*   Updated: 2024/01/08 15:59:17 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// saves the RGB values of the F and C elements
// check if RGB is correct?
void	get_colour_value(char *file, t_rgba *col)
{
	skip_spaces(&file);
	col->r = ft_atoi(file);
	while (*file && *file != ',')
		file++;
	if (*file == ',')
		file++;
	col->g = ft_atoi(file);
	while (*file && *file != ',')
		file++;
	if (*file == ',')
		file++;
	col->b = ft_atoi(file);
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
bool	is_texture(char *file)
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
bool is_colour(char *file)
{
	if (*file == 'F')
		return (true);
	if (*file == 'C')
		return (true);
	return (false);
}
