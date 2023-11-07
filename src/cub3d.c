/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cub3d.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/07 15:36:26 by jboeve        #+#    #+#                 */
/*   Updated: 2023/11/07 17:27:26 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <meta.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "MLX42/MLX42.h"

#define WIDTH 256
#define HEIGHT 256

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int cub3d(int argc, char *argv[])
{
	t_meta meta;
	(void)argc;
	(void)argv;

	// MLX allows you to define its core behaviour before startup.
	meta.mlx = mlx_init(WIDTH, HEIGHT, "window", true);
	if (!meta.mlx)
		ft_error();

	// Create and display the image.
	mlx_image_t* img = mlx_new_image(meta.mlx, 256, 256);
	if (!img || (mlx_image_to_window(meta.mlx, img, 0, 0) < 0))
		ft_error();
	mlx_loop_hook(meta.mlx, graphics_draw, &meta);
	mlx_terminate(meta.mlx);
	return 0;
}
