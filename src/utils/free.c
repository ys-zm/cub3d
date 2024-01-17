/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <yzaim@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:53:55 by yzaim         #+#    #+#                 */
/*   Updated: 2024/01/17 16:13:14 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"

static void	free_t_tex(t_attr *attributes)
{
	free(attributes->n.tex_path);
	free(attributes->s.tex_path);
	free(attributes->e.tex_path);
	free(attributes->w.tex_path);
	mlx_delete_texture(attributes->n.tex);
	mlx_delete_texture(attributes->s.tex);
	mlx_delete_texture(attributes->e.tex);
	mlx_delete_texture(attributes->w.tex);
}

void	meta_free(t_meta *meta)
{
	free_t_tex(&(meta->attributes));
	free(meta->map.level);
	// if (meta->map_element)
	// 	free(meta->map_element);
}
