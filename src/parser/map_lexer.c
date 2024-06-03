/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_lexer.c                                       :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:30:18 by yzaim         #+#    #+#                 */
/*   Updated: 2024/05/29 12:24:26 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "logging.h"
#include <stdio.h>

// returns true if the next line only has spaces
bool	nl_only_spaces(char *file)
{
	if (*file)
	{
		file++;
		if (*file == '\n')
		{
			file++;
			while (*file == ' ' && *file)
				file++;
			if (*file == '\n')
				return (true);
			return (false);
		}
	}
	return (false);
}

// find the index of the end of the map element 
int	end_of_map(char *file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (nl_only_spaces(&file[i]) || ((!valid_map_char(file[i]) && file[i] != '\n')))
		{
			break ;
		}
		if (valid_map_char(file[i]) || file[i] == '\n')
			i++;
	}
	return (i);
}

void	skip_map_element(char **file, int *skip)
{
	*skip = 0;
	while (*file)
	{
		if (is_map_element(*file))
			skip_line(file, 1);
		if (only_spaces(*file) || !is_map_element(*file))
			break ;
	}
}

// inputs the map into map->element
int	input_map_lexer(char *file, t_map *map)
{
	int	i;

	i = 0;
	if (*file)
	{
		i = end_of_map(file);
		map->map_element = ft_substr(file, 0, i + 1);
		if (!map->map_element)
			return (pr_err(MALL_ERR));
		return (EXIT_SUCCESS);
	}
	return (pr_err(MISSING_MAP));
}

/* map_lex returns an error if
1) the map element exists already (that means there are two maps in the file)
2) if the map element is reached before mandatory elements
 are found (N, S, E, W)*/
int	map_lex(char **file, t_map *map, int *skip, int mandatory)
{
	int	exit_code;

	if (map->map_element != NULL)
	{
		exit_code = pr_err(DUP_ELEMENTS);
	}
	else if (mandatory == 6)
	{
		exit_code = input_map_lexer(*file, map);
	}
	else
	{
		exit_code = pr_err(FILE_ORDER);
	}
	skip_map_element(file, skip);
	return (exit_code);
}
