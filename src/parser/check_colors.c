/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_colors.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:30:18 by yzaim         #+#    #+#                 */
/*   Updated: 2024/03/06 14:25:01 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "logging.h"

static bool	valid_colour(char *content)
{
	size_t	commas;

	commas = 0;
	while (*content)
	{
		if (*content == ',')
			commas++;
		if (!ft_isdigit(*content) && *content != ',' && \
				*content != ' ' && *content != '\t')
			return (false);
		content++;
	}
	return (commas == 2);
}

static void	free_2d_array(char **arr)
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
