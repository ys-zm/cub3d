/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                            :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <yzaim@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:53:55 by yzaim         #+#    #+#                 */
/*   Updated: 2024/02/07 12:04:35 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"

// Danger with freeing everything at the end? If allocation of one fails, you should free everything in the same function, dont wait until the end

void	f_tex(t_tex *attr)
{
	if (attr->tex_path)
		free(attr->tex_path);
	if (attr->tex)
	{
		mlx_delete_texture(attr->tex);
	}
}

static void	free_t_tex(t_attr *attributes)
{
	f_tex(&attributes->n);
	f_tex(&attributes->s);
	f_tex(&attributes->e);
	f_tex(&attributes->w);
	f_tex(&attributes->f);
	f_tex(&attributes->c);
	f_tex(&attributes->c_alt);
}

void	free_t_flag_list(t_flag **list)
{
	t_flag *l;

	while (*list != NULL)
	{
		l = (*list);
		(*list) = (*list)->next;
		if (l->flag)
			free(l->flag);
		if (l->content)
			free(l->content);
		free(l);
	}
}

void	free_t_sprites(t_sprite **sprites, uint32_t sprite_count)
{
	t_sprite	*arr;
	uint32_t	i;

	i = 0;
	arr = *sprites;
	while (i < sprite_count)
	{
		f_tex(&arr[i].tex);
		i++;
	}
	free(*sprites);
}

void	meta_free(t_meta *meta)
{
	free_t_tex(&meta->attributes);
	free(meta->map.level);
	free_t_sprites(&meta->attributes.sprites, meta->attributes.sprite_count);
	free(meta->player.sprite_dist);
	free(meta->player.sprite_order);
}
