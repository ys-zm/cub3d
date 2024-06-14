/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_fill.c                                     :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:43:19 by yzaim         #+#    #+#                 */
/*   Updated: 2024/06/14 10:37:11 by yesimzaim     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "logging.h"
#include "libft.h"
#include "meta.h"
#include <string.h>

static char	**get_path(t_attr *attributes, char *flag)
{
	if (!ft_strcmp_largest(flag, "NO"))
		return (&attributes->n.tex_path);
	if (!ft_strcmp_largest(flag, "SO"))
		return (&attributes->s.tex_path);
	if (!ft_strcmp_largest(flag, "WE"))
		return (&attributes->w.tex_path);
	if (!ft_strcmp_largest(flag, "EA"))
		return (&attributes->e.tex_path);
	if (!ft_strcmp_largest(flag, "F"))
		return (&attributes->f.tex_path);
	if (!ft_strcmp_largest(flag, "C"))
		return (&attributes->c.tex_path);
	if (!ft_strcmp_largest(flag, "C_ALT"))
		return (&attributes->c_alt.tex_path);
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
	if (!ft_strcmp_largest(*path, ""))
		return (pr_err(M_PATH), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// add check for RBG code correctness?
int	input_colour(t_attr *attributes, char *flag, char *content)
{
	t_rgba		*col_path;

	if (!ft_strcmp_largest(flag, "F"))
		col_path = &attributes->floor_c;
	else if (!ft_strcmp_largest(flag, "C_ALT"))
		col_path = &attributes->ceil_alt_c;
	else if (!ft_strcmp_largest(flag, "C"))
		col_path = &attributes->ceiling_c;
	else if (!ft_strcmp_largest(flag, "NO"))
		col_path = &attributes->n_c;
	else if (!ft_strcmp_largest(flag, "SO"))
		col_path = &attributes->s_c;
	else if (!ft_strcmp_largest(flag, "EA"))
		col_path = &attributes->e_c;
	else if (!ft_strcmp_largest(flag, "WE"))
		col_path = &attributes->w_c;
	if (!get_colour_value(content, col_path))
		return (pr_err(COLOR_CODE_WRONG), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
