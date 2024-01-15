/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <yzaim@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:53:55 by yzaim         #+#    #+#                 */
/*   Updated: 2024/01/08 15:55:28 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"

static void	free_t_tex(t_attr *attributes)
{
	free(attributes->n.tex_path);
	free(attributes->s.tex_path);
	free(attributes->e.tex_path);
	free(attributes->w.tex_path);
}

void	meta_free(t_meta *meta)
{
	free_t_tex(&(meta->attributes));
	free(meta->map.level);
	// if (meta->map_element)
	// 	free(meta->map_element);
}
