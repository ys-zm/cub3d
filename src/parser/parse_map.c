/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:26:06 by yzaim         #+#    #+#                 */
/*   Updated: 2024/01/24 11:02:13 by yzaim         ########   odam.nl         */
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

int	input_map(t_meta *meta, char *file)
{
	int	i;
	
	while (*file)
	{
		skip_spaces(&file);
		if (is_wall(file) || is_floor_or_ceiling(file) || only_spaces(file))
			skip_line(&file);
		else
			break ;
	}
	if (*file)
	{
		i = ft_strlen(file);
		meta->map_element = ft_substr(file, 0, i);
		if (!meta->map_element)
			return (pr_err(MALL_ERR));
		return (EXIT_SUCCESS);
	}
	return (pr_err(MISSING_MAP), EXIT_FAILURE);
}
