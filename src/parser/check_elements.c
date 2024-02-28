/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_elements.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:33:58 by yzaim         #+#    #+#                 */
/*   Updated: 2024/02/14 17:42:12 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

// checks if the element abbreviations are valid
bool	is_valid_element(char *file)
{
	const char	*el[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	size_t		i;

	i = 0;
	while (i < 6)
	{
		if (!ft_strncmp(file, el[i], ft_strlen(el[i]) + 1))
		{
			return (true);
		}
		i++;
	}
	return (false);
}

// returns true if there are only spaces until '\0' or '\n'
bool	only_spaces(char *file)
{
	while (*file && *file == ' ')
		file++;
	if (*file == '\0' || *file == '\n')
		return (true);
	return (false);
}

// returns true if the map element is reached
bool	is_map_element(char *file)
{
	while (*file && valid_map_char(*file))
		file++;
	if (*file == '\0' || *file == '\n')
	{
		return (true);
	}
	return (false);
}

bool	check_missing(int *found)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (found[i] == 0)
			return (pr_err(MISSING_ELEMENTS), true);
		i++;
	}
	return (false);
}

// returns true if there are duplicate elements
bool	is_duplicate(char *file)
{
	const char	element[6] = {'N', 'S', 'W', 'E', 'F', 'C'};
	int			found[6];
	int			i;

	ft_bzero(found, sizeof(found));
	while (*file)
	{
		i = 0;
		skip_spaces(&file);
		if ((is_valid_element(file) || is_floor_or_ceiling(file)))
		{
			while (*file && *file != element[i] && i < 6)
				i++;
			if (found[i] == 0)
				found[i] = 1;
			else
				return (pr_err(DUP_ELEMENTS), true);
		}
		skip_line(&file, 1);
	}
	return (false);
}
