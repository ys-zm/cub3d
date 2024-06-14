/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_elements.c                                  :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:43:19 by yzaim         #+#    #+#                 */
/*   Updated: 2024/06/14 10:07:19 by yesimzaim     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "logging.h"

// TODO: Add ft_strlen_largest()
static t_element_type	check_element_type(char *flag)
{
	if (!ft_strcmp_largest(flag, "C") || !ft_strcmp_largest(flag, "F") || !ft_strcmp_largest(flag, "C_ALT"))
		return (CEIL_FLOOR);
	if (is_wall(flag))
		return (WALL);
	if (!ft_strcmp_largest(flag, "SP"))
		return (SPRITE);
	if (!ft_strcmp_largest(flag, "D"))
		return (DOOR);
	if (!ft_strcmp_largest(flag, "LVL"))
		return (NEXT_LVL);
	return (INVALID);
}

static int	handle_texture_col(t_attr *attributes, char *flag, char *content)
{
	int	exit_code;

	exit_code = 0;
	if (is_path(content))
	{
		exit_code = input_texture_path(attributes, flag, content);
	}
	else
	{
		exit_code = input_colour(attributes, flag, content);
	}
	return (exit_code);
}

static int	handle_element(t_meta *meta, t_element_type type, char *flag, char *content)
{
	int	exit_code;

	exit_code = 0;
	if (type == CEIL_FLOOR)
		exit_code = handle_texture_col(&meta->attributes, flag, content);
	else if (type == WALL)
		exit_code = handle_texture_col(&meta->attributes, flag, content);
	else if (type == SPRITE)
		exit_code = input_sprite_data(&meta->attributes.sprites, &meta->attributes.sprite_arr_index, content);
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
	meta->attributes.doors.door_count = count_doors(meta->map.level, meta->map.width, meta->map.height);
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
