/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <yzaim@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:53:55 by yzaim         #+#    #+#                 */
/*   Updated: 2024/01/24 11:22:41 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"

// Danger with freeing everything at the end? If allocation of one fails, you should free everything in the same function, dont wait until the end
static void	free_t_tex(t_attr *attributes)
{
	if (attributes->n.tex_path)
	{
		free(attributes->n.tex_path);
		mlx_delete_texture(attributes->n.tex);
	}
	if (attributes->s.tex_path)
	{
		free(attributes->s.tex_path);
		mlx_delete_texture(attributes->s.tex);
	}
	if (attributes->e.tex_path)
	{
		free(attributes->e.tex_path);
		mlx_delete_texture(attributes->e.tex);
	}
	if (attributes->w.tex_path)
	{
		free(attributes->w.tex_path);
		mlx_delete_texture(attributes->w.tex);
	}	
	if (attributes->f.tex_path)
	{
		free(attributes->f.tex_path);
		mlx_delete_texture(attributes->f.tex);
	}
	if (attributes->c.tex_path)
	{
		free(attributes->c.tex_path);
		mlx_delete_texture(attributes->c.tex);
	}
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
		if (arr[i].tex.tex_path)
		{
			free(arr[i].tex.tex_path);
			mlx_delete_texture(arr[i].tex.tex);
		}
		i++;
	}
	free(*sprites);
}

void	meta_free(t_meta *meta)
{
	free_t_tex(&(meta->attributes));
	free(meta->map.level);
	if (meta->attributes.sprites)
		free_t_sprites(&meta->attributes.sprites, meta->attributes.sprite_count);
}
