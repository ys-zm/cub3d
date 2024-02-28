/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_elements.c                                  :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:43:19 by yzaim         #+#    #+#                 */
/*   Updated: 2024/02/28 13:31:41 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "error.h"

int	input_path(char **path, char *content)
{
	if (*path)
		return (EXIT_SUCCESS);
	*path = ft_strdup(content);
	if (!*path)
		return (pr_err(MALL_ERR), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


// // saves path value and checks of value us empty
// int	input_texture_path(t_attr *attributes, char *flag, char *content)
// {
// 	char	element[6] = {'N', 'S', 'W', 'E', 'F', 'C'};
// 	char**	path[6] = {&attributes->n.tex_path, &attributes->s.tex_path, &attributes->w.tex_path, &attributes->e.tex_path, &attributes->f.tex_path, &attributes->c.tex_path};
// 	int i;
//
// 	i = 0;
// 	while (i < 6)
// 	{
// 		if (*flag && *flag == element[i])
// 		{
// 			if (input_path(path[i], content))
// 			{
// 				return (EXIT_FAILURE);
// 			}
// 		}
// 		i++;
// 	}
// 	return (EXIT_SUCCESS);
// }

t_element_type	check_element_type(char *flag)
{
	if (!ft_strncmp(flag, "C", 1) || !ft_strncmp(flag, "F", 1) \
	|| !ft_strncmp(flag, "C_ALT", 4))
		return (CEIL_FLOOR);
	if (is_wall(flag))
		return (WALL);
	if (!ft_strncmp(flag, "SP", 2))
		return (SPRITE);
	if (!ft_strncmp(flag, "DR", 2))
		return (DOOR);
	if (!ft_strncmp(flag, "LVL", 3))
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

int	input_sprite_data(t_sprite **sprites_array, uint32_t *i ,char *content)
{
	t_sprite	*arr = *sprites_array;
	char		*tex_path;
	char		*pos_x;
	char		*pos_y;

	if (!valid_sprite_content(content))
		return (pr_err(SP_CONTENT), EXIT_FAILURE);

	arr[*i].tex.tex_path = find_sprite_val(&content);
	pos_x = find_sprite_val(&content);
	pos_y = find_sprite_val(&content);

	if (!is_double(pos_x) || !is_double(pos_y))
		return (EXIT_FAILURE);

	arr[*i].pos.x = ft_atod(pos_x);
	arr[*i].pos.y = ft_atod(pos_y);
	free(pos_x);
	free(pos_y);
	(*i)++;
	return (EXIT_SUCCESS);
}

int	handle_element(t_meta *meta, t_element_type type, char *flag, char *content)
{
	int	exit_code;

	if (type == CEIL_FLOOR)
		exit_code = handle_ceil_floor(&meta->attributes, flag, content);
	else if (type == WALL)
		exit_code = input_texture_path(&meta->attributes, flag, content);
	else if (type == SPRITE)
		exit_code = input_sprite_data(&meta->attributes.sprites, &meta->attributes.sprite_arr_index, content);
	else if (type == DOOR)
		exit_code = input_path(&meta->attributes.doors.tex.tex_path, content);
	else if (type == NEXT_LVL)
		exit_code = input_path(&meta->next_level, content);
	return (exit_code);
}

uint32_t	count_doors(t_cell_type *map, uint32_t w, uint32_t h)
{
	uint32_t	doors;
	uint32_t	i;

	doors = 0;
	i = 0;
	while (i < w * h)
	{
		if (map[i] == MAP_DOOR_CLOSED)
			doors++;
		i++;
	}
	return (doors);
}

int	save_door_index(uint32_t *arr, uint32_t door_count, t_map map)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	while (i < map.width * map.height)
	{
		if (map.level[i] == MAP_DOOR_CLOSED)
		{
			arr[j] = i;
			if (j < door_count)
				j++;
			else
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	set_doors(t_door *doors, t_map map)
{
	if (!doors->door_count)
		return (EXIT_SUCCESS);
	doors->idx = malloc(sizeof(uint32_t) * doors->door_count);
	if (!doors->idx)
		return (pr_err(MALL_ERR));
	if (save_door_index(doors->idx, doors->door_count, map))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int parse_elements(t_meta *meta)
{
	t_flag *elements = meta->elements;
	t_cell_type type;

	meta->attributes.sprite_count = count_sprites(meta->elements);
	meta->attributes.doors.door_count = count_doors(meta->map.level, meta->map.width, meta->map.height);
	meta->attributes.sprite_arr_index = 0;

	if(set_doors(&meta->attributes.doors, meta->map))
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
