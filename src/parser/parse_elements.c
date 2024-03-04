/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_elements.c                                  :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:43:19 by yzaim         #+#    #+#                 */
/*   Updated: 2024/03/04 11:45:55 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "error.h"

// TODO: Add ft_strlen_largest()
t_element_type	check_element_type(char *flag)
{
	if (!ft_strncmp(flag, "C", 1) || !ft_strncmp(flag, "F", 1) \
	|| !ft_strncmp(flag, "C_ALT", 5))
		return (CEIL_FLOOR);
	if (is_wall(flag))
		return (WALL);
	if (!ft_strncmp(flag, "SP", 3))
		return (SPRITE);
	if (!ft_strncmp(flag, "D", 2))
		return (DOOR);
	if (!ft_strncmp(flag, "LVL", 4))
		return (NEXT_LVL);
	return (INVALID);
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

	exit_code = 0;
	if (type == CEIL_FLOOR)
		exit_code = handle_ceil_floor(&meta->attributes, flag, content);
	else if (type == WALL)
		exit_code = input_texture_path(&meta->attributes, flag, content);
	else if (type == SPRITE)
		exit_code = input_sprite_data(&meta->attributes.sprites, \
						&meta->attributes.sprite_arr_index, content);
	else if (type == DOOR)
		exit_code = input_path(&meta->attributes.doors.tex.tex_path, content);
	else if (type == NEXT_LVL)
		exit_code = input_path(&meta->next_level, content);
	return (exit_code);
}

int	parse_elements(t_meta *meta)
{
	const t_flag	*elements = meta->elements;
	t_element_type	type;

	meta->attributes.sprite_count = count_sprites(meta->elements);
	meta->attributes.doors.door_count = count_doors(meta->map.level, \
									meta->map.width, meta->map.height);
	meta->attributes.sprite_arr_index = 0;
	if (set_doors(&meta->attributes.doors, meta->map))
		return (EXIT_FAILURE);
	if (set_up_sprites(meta))
		return (EXIT_FAILURE);
	while (elements != NULL)
	{
		type = check_element_type(elements->flag);
		if (type != INVALID)
		{
			if (handle_element(meta, type, elements->flag, elements->content))
				return (free_t_flag_list(&meta->elements), EXIT_FAILURE);
		}
		elements = elements->next;
	}
	free_t_flag_list(&meta->elements);
	return (EXIT_SUCCESS);
}
