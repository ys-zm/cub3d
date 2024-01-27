/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   mlx_switch_shader.c                               :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/01/27 18:59:14 by joppe         #+#    #+#                 */
/*   Updated: 2024/01/27 20:34:55 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "MLX42/MLX42.h"
#include "MLX42/MLX42_Int.h"
#include <stdint.h>
#include <stdio.h>

void mlx_switch_shader(mlx_t *mlx, shader_program_t prog)
{
	mlx_ctx_t* mlxctx = mlx->context;
	
	if (prog == MLX_PROG_DEFAULT)
		glUseProgram(mlxctx->shaderprogram);
	else if (prog == MLX_PROG_CUSTOM)
		glUseProgram(mlxctx->shaderprogram_alt);
}

uint32_t mlx_create_tex(mlx_t *mlx)
{
	uint32_t texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return texture;
}

void mlx_render(mlx_t* mlx, const uint32_t w, const uint32_t h, const uint32_t tex, const uint32_t *pixels)
{
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

}
