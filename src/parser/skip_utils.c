/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   skip_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:30:18 by yzaim         #+#    #+#                 */
/*   Updated: 2024/02/14 17:35:26 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// skips a line on the file until '\n' char
void	skip_line(char **file, int to_skip)
{
	if (!to_skip)
		return ;
	while (file && *file && **file && **file != '\n')
		(*file)++;
	if (**file == '\n')
		(*file)++;
}

// skips all spaces in a line
void	skip_spaces(char **file)
{
	while (file && *file && **file && (**file == ' ' || **file == 9))
		(*file)++;
}

void	skip_digits(char **file)
{
	while (file && *file && **file && ft_isdigit(**file))
		(*file)++;
	skip_spaces(file);
	if (**file == ',')
		(*file)++;
}

int	valid_map_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' \
	|| c == 'E' || c == 'W' || c == ' ');
}

int	player_pos_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
