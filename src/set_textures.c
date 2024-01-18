/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_textures.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <yzaim@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:56:45 by yzaim         #+#    #+#                 */
/*   Updated: 2024/01/08 15:59:17 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "meta.h"

int	set_textures(t_attr *attributes)
{
	attributes->n.tex = mlx_load_png(attributes->n.tex_path);
	if (attributes->n.tex == NULL)
		return (pr_err(MLX_ERROR));
	attributes->s.tex = mlx_load_png(attributes->s.tex_path);
	if (attributes->s.tex == NULL)
		return (pr_err(MLX_ERROR));
	attributes->e.tex = mlx_load_png(attributes->e.tex_path);
	if (attributes->e.tex == NULL)
		return (pr_err(MLX_ERROR));
	attributes->w.tex = mlx_load_png(attributes->w.tex_path);
	if (attributes->w.tex == NULL)
		return (pr_err(MLX_ERROR));
	return (EXIT_SUCCESS);
}

