/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_elements.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:43:19 by yzaim         #+#    #+#                 */
/*   Updated: 2024/02/14 13:18:51 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// saves path value and checks of value us empty
int	input_texture_path(t_attr *attributes, char *flag, char *content)
{
	char	element[6] = {'N', 'S', 'W', 'E', 'F', 'C'};
	char	**path[6] = {&attributes->n.tex_path, &attributes->s.tex_path, \
				&attributes->w.tex_path, &attributes->e.tex_path, \
				&attributes->f.tex_path, &attributes->c.tex_path};
	int		i;

	i = 0;
	while (i < 6)
	{
		if (*flag && *flag == element[i])
		{
			*path[i] = get_tex_val(content);
			if (!(path[i]))
				return (pr_err(MALL_ERR), EXIT_FAILURE);
			if (!ft_strncmp(*path[i], "", 1))
				return (pr_err(M_PATH), EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

// add check for RBG code correctness?
int	input_colour(t_attr *attributes, char *flag, char *content)
{
	char	tx[2] = {'F', 'C'};
	t_rgba	*st[2] = {&attributes->floor_c, &attributes->ceiling_c};
	int		i;

	i = 0;
	while (i < 2 && *flag && *flag != tx[i])
		i++;
	get_colour_value(content, st[i]);
	return (EXIT_SUCCESS);
}

t_element_type	check_element_type(char *flag)
{
	if (!ft_strncmp(flag, "C", 1) || !ft_strncmp(flag, "F", 1))
		return (CEIL_FLOOR);
	if (is_wall(flag))
		return (WALL);
	if (!ft_strncmp(flag, "SP", 2))
		return (SPRITE);
	if (!ft_strncmp(flag, "DR", 2))
		return (DOOR);
	return (NON_VALID);
}

int	handle_ceil_floor(t_attr *attributes, char *flag, char *content)
{
	int	exit_code;

	exit_code = 0;
	if (is_path(content))
	{
		exit_code = input_texture_path(attributes, flag, content);
	}
	else
	{
		if (!is_valid_color(content))
			return (pr_err(COLOR_CODE_WRONG));
		exit_code = input_colour(attributes, flag, content);
	}
	return (exit_code);
}

int	handle_element(t_meta *meta, t_element_type type, char *flag, char *content)
{
	int	exit_code;

	if (type == CEIL_FLOOR)
		exit_code = handle_ceil_floor(&meta->attributes, flag, content);
	else if (type == WALL)
		exit_code = input_texture_path(&meta->attributes, flag, content);
	else if (type == SPRITE)
	{
		exit_code = input_sprite_texture_path(&meta->attributes.sprites,\
		&meta->attributes.sprite_arr_index, content);
	}
	return (exit_code);
}

int	parse_elements(t_meta *meta)
{
	t_flag			*elements;
	t_element_type	type;

	elements = meta->elements;
	meta->attributes.sprite_count = count_sprites(meta->elements);
	meta->attributes.sprite_arr_index = 0;
	if (set_up_sprites(meta))
		return (EXIT_FAILURE);
	while (elements != NULL)
	{
		type = check_element_type(elements->flag);
		if (type != NON_VALID)
			handle_element(meta, type, elements->flag, elements->content);
		elements = elements->next;
	}
	free_t_flag_list(&meta->elements);
	return (EXIT_SUCCESS);
}
