/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_textures.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <yzaim@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:56:45 by yzaim         #+#    #+#                 */
/*   Updated: 2024/03/04 17:19:56 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "logging.h"

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
