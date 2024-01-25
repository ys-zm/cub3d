/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_textures.c                                    :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <yzaim@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:56:45 by yzaim         #+#    #+#                 */
/*   Updated: 2024/01/25 00:29:36 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "meta.h"
#include <stdio.h>

int	set_floor_and_ceiling_textures(t_attr *attributes)
{
	if (attributes->f.tex_path != NULL)
	{
		attributes->f.tex = mlx_load_png(attributes->f.tex_path);
		if (attributes->f.tex == NULL)
			return (EXIT_FAILURE);
	}
	if (attributes->c.tex_path != NULL)
	{
		attributes->c.tex = mlx_load_png(attributes->c.tex_path);
		if (attributes->c.tex == NULL)
			return (EXIT_FAILURE);
	}

	attributes->c_alt.tex = mlx_load_png("texture_examples/window_square.png");
	if (attributes->c_alt.tex == NULL)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}

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
	if (set_floor_and_ceiling_textures(attributes))
		return (pr_err(MLX_ERROR));
	return (EXIT_SUCCESS);
}

