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

