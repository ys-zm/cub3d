/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_colours.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:43:19 by yzaim         #+#    #+#                 */
/*   Updated: 2024/02/14 17:50:07 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "meta.h"

char	**get_path(t_attr *attributes, char *flag)
{
	if (*flag == 'N')
		return (&attributes->n.tex_path);
	if (*flag == 'S')
		return (&attributes->s.tex_path);
	if (*flag == 'W')
		return (&attributes->w.tex_path);
	if (*flag == 'E')
		return (&attributes->e.tex_path);
	if (*flag == 'F')
		return (&attributes->f.tex_path);
	if (*flag == 'C')
		return (&attributes->c.tex_path);
	return (NULL);
}

// saves path value and checks of value us empty
int	input_texture_path(t_attr *attributes, char *flag, char *content)
{
	char	**path;

	path = get_path(attributes, flag);
	*path = get_tex_val(content);
	if (!path)
		return (pr_err(MALL_ERR), EXIT_FAILURE);
	if (!ft_strncmp(*path, "", 1))
		return (pr_err(M_PATH), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// add check for RBG code correctness?
int	input_colour(t_attr *attributes, char *flag, char *content)
{
	t_rgba		*col_path;

	if (*flag == 'F')
		col_path = &attributes->floor_c;
	else
		col_path = &attributes->ceiling_c;
	get_colour_value(content, col_path);
	return (EXIT_SUCCESS);
}
