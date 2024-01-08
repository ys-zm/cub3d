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

static void	free_t_tex(t_tex *tex)
{
	free(tex->no);
	free(tex->so);
	free(tex->ea);
	free(tex->we);
}

void	meta_free(t_meta *meta)
{
	free_t_tex(&(meta->tex));
	free(meta->map.level);
	if (meta->map_element)
	free(meta->map_element);
}
