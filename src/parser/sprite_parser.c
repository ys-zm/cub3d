/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_parser.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:43:19 by yzaim         #+#    #+#                 */
/*   Updated: 2024/03/04 15:16:04 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "logging.h"
#include "stdbool.h"

char	*find_sprite_val(char **content)
{
	char	*val;
	char	*c;
	int		i;

	i = 0;
	c = *content;
	while (c[i] != '\0')
	{
		if (c[i] == ' ' || c[i] == '\t')
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

int	input_sprite_data(t_sprite **sprites_array, \
								uint32_t *i, char *content)
{
	t_sprite	*arr;
	char		*pos_x;
	char		*pos_y;

	arr = *sprites_array;
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

int	set_up_sprites(t_meta *meta)
{
	if (meta->attributes.sprite_count)
	{
		meta->attributes.sprites = calloc(meta->attributes.sprite_count, \
										sizeof(t_sprite));
		if (!meta->attributes.sprites)
			return (pr_err(MALL_ERR), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

uint32_t	count_sprites(t_flag *elements)
{
	uint32_t	count;

	count = 0;
	while (elements != NULL)
	{
		if (!ft_strcmp_largest(elements->flag, "SP"))
			count++;
		elements = elements->next;
	}
	return (count);
}

bool	valid_sprite_content(char *content)
{
	uint32_t	content_count;
	uint16_t	i;
	bool		word;

	i = 0;
	content_count = 0;
	word = false;
	while (content[i])
	{
		if (content[i] != ' ' && content[i] != '\t' && content[i] != '\0')
			word = true;
		if ((content[i] == ' ' || content[i] == '\t') && word)
		{
			content_count++;
			word = false;
		}
		i++;
	}
	if (word && content[i] == '\0')
		content_count++;
	if (content_count == 3)
		return (true);
	return (false);
}
