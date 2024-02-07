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
int	input_texture_path(t_attr *attributes, char *flag, char *content)
{
	char	element[6] = {'N', 'S', 'W', 'E', 'F', 'C'};
	char**	path[6] = {&attributes->n.tex_path, &attributes->s.tex_path, &attributes->w.tex_path, &attributes->e.tex_path, &attributes->f.tex_path, &attributes->c.tex_path};
	int i;

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
	t_rgba  *st[2] = {&attributes->floor_c, &attributes->ceiling_c};
	int	i;

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
	int exit_code = 0;

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

char	*find_sprite_val(char **content)
{
	char	*val;
	char	*c;
	int	i;

	i = 0;	
	c = *content;
	while (c[i] != '\0')
	{
		if (c[i] == ' ')
		{
			break ;
		}
		i++;
	}
	if (i)
	{
		val = ft_substr(c, 0, i);
		if (!val)
			return (pr_err(MALL_ERR), NULL);
		*content += i;
		skip_spaces(content);
		return (val);
	}
	return (ft_strdup(""));
}

int	input_sprite_texture_path(t_sprite **sprites_array, uint32_t *i ,char *content)
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
	int exit_code;

	if (type == CEIL_FLOOR)
		exit_code = handle_ceil_floor(&meta->attributes, flag, content);
	else if (type == WALL)
		exit_code = input_texture_path(&meta->attributes, flag, content);
	else if (type == SPRITE)
	{
		exit_code = input_sprite_texture_path(&meta->attributes.sprites, &meta->attributes.sprite_arr_index, content);
		// printf("%d. SP %s %lf %lf\n", 0, meta->attributes.sprites[0].tex.tex_path, meta->attributes.sprites[0].pos.x, meta->attributes.sprites[0].pos.y);
	}
	return (exit_code);
}

int	set_up_sprites(t_meta *meta)
{
	if (meta->attributes.sprite_count)
	{
		meta->attributes.sprites = calloc(meta->attributes.sprite_count, sizeof(t_sprite));
		if (!meta->attributes.sprites)
			return (pr_err(MALL_ERR), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

uint32_t	count_doors(t_cell_type *map, uint32_t w, uint32_t h)
{
	uint32_t	doors;
	uint32_t	i;

	doors = 0;
	i = 0;
	while (i < w * h)
	{
		if (map[i] == MAP_DOOR)
			doors++;
		i++;
	}
	return (doors);
}

int	save_index(t_door *doors, uint32_t door_count)
{
	uint32_t	i;

	i = 0;
}

int	set_doors(t_meta *meta)
{
	meta.attributes.doors = malloc(sizeof(t_door) * meta.attributes.door_count);
	if (!meta.attributes.doors)
		return (pr_err(MALL_ERR));

}

int parse_elements(t_meta *meta)
{
	t_flag *elements = meta->elements;
	meta->attributes.sprite_count = count_sprites(meta->elements);
	meta.attributes.door_count = count_doors(meta.map.level, meta.map.width, meta.map.height);
	meta->attributes.sprite_arr_index = 0;

	if (meta.attributes.door_count)
	{
		// save door idx
	}
	if (set_up_sprites(meta))
		return (EXIT_FAILURE);
	while (elements != NULL)
	{
		t_element_type type = check_element_type(elements->flag);
		if (type != NON_VALID)
			handle_element(meta, type, elements->flag, elements->content);
		elements = elements->next;
	}
	free_t_flag_list(&meta->elements);
	return (EXIT_SUCCESS);
}
