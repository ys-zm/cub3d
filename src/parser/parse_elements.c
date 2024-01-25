/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_elements.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:43:19 by yzaim         #+#    #+#                 */
/*   Updated: 2024/01/24 11:21:34 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// saves path value and checks of value us empty
int	input_texture(t_attr *attributes, char *file)
{
	char	element[6] = {'N', 'S', 'W', 'E', 'F', 'C'};
	char**	path[6] = {&attributes->n.tex_path, &attributes->s.tex_path, &attributes->w.tex_path, &attributes->e.tex_path, &attributes->f.tex_path, &attributes->c.tex_path};
	int i;

	i = 0;
	skip_spaces(&file);
	while (i < 6)
	{
		if (*file && *file == element[i])
		{
			*path[i] = get_tex_val(file + 2);
			if (!(path[i]))
				return (pr_err(MALL_ERR), EXIT_FAILURE);
			if (!ft_strncmp(*path[i], "", 1))
				return (pr_err(M_PATH), EXIT_FAILURE);
			// break ;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

// add check for RBG code correctness?
int	input_colour(t_attr *attributes, char *file)
{
	char	tx[2] = {'F', 'C'};
	t_rgba  *st[2] = {&attributes->floor_c, &attributes->ceiling_c};
	int	i;

	i = 0;
	skip_spaces(&file);
	while (i < 2 && *file && *file != tx[i])
		i++;
	get_colour_value(file + 1, st[i]);
	return (EXIT_SUCCESS); 
}

int save_elements(t_attr *attributes, char *file)
{
	while (*file)
	{
		skip_spaces(&file);
		if (is_wall(file))
		{
			if (input_texture(attributes, file))
				return (EXIT_FAILURE);
		}
		else if (is_floor_or_ceiling(file))
		{
			if (is_path(file))
			{
				printf("here i come\n");
				if (input_texture(attributes, file))
					return (EXIT_FAILURE);
			}
			else 
			{
				if (input_colour(attributes, file))
					return (EXIT_FAILURE);
			}
		}
		skip_line(&file);
	}
	return (EXIT_SUCCESS);
}

int parse_elements(t_meta *meta, char *file)
{
	if (!elements_order(file) || is_duplicate(file) || is_missing(file) || !colors_valid(file))
		return (free(file), EXIT_FAILURE);
	if (save_elements(&(meta->attributes), file))
		return (free(file), EXIT_FAILURE);
	if (input_map(meta, file))
		return (free(file),EXIT_FAILURE);
	free(file);
	return (EXIT_SUCCESS);
}
