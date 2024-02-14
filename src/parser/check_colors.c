/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_colors.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:30:18 by yzaim         #+#    #+#                 */
/*   Updated: 2024/02/14 13:01:18 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// check if color code values are between 0-255
bool	valid_rgb_value(char *file)
{
	int	i;

	i = 0;
	skip_spaces(&file);
	while (file[i] && ft_isdigit(file[i]))
		i++;
	if (!i)
		return (false);
	if (i > 3)
		return (false);
	if (i == 3)
	{
		if (file[0] > '2')
			return (false);
		if (file[0] == '2' && file[1] > '5')
			return (false);
		if (file[0] == '2' && file[1] == '5' && file[2] > '5')
			return (false);
	}
	return (true);
}

bool	is_valid_color(char *file)
{
	int	i;

	i = 0;
	if (*file && (*file == 'F' || *file == 'C'))
	{
		file++;
		while (i < 3)
		{
			skip_spaces(&file);
			if (!valid_rgb_value(file))
				return (pr_err(COLOR_CODE_WRONG), false);
			skip_digits(&file);
			i++;
		}
	}
	return (true);
}

bool	colors_valid(char *file)
{
	while (*file)
	{
		skip_spaces(&file);
		if (is_valid_element(file))
		{
			if (!is_path(file) && is_floor_or_ceiling(file) && !is_valid_color(file))
				return (false);
		}
		skip_line(&file, 1);
	}
	return (true);
}
