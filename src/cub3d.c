/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cub3d.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/07 15:36:26 by jboeve        #+#    #+#                 */
/*   Updated: 2023/11/08 23:36:36 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "meta.h"
#include "MLX42/MLX42.h"


// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int cub3d(int argc, char *argv[])
{
	t_meta	meta;
	UNUSED(argc);
	UNUSED(argv);

	// MLX allows you to define its core behaviour before startup.
	meta.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, true);
	if (!meta.mlx)
	{
		ft_error();
		return EXIT_FAILURE;
	}

	// Create and display the image.
	meta.image = mlx_new_image(meta.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!meta.image || (mlx_image_to_window(meta.mlx, meta.image, 0, 0) < 0))
	{
		ft_error();
		return EXIT_FAILURE;
	}
	game_init(&meta);
	mlx_loop_hook(meta.mlx, game_loop, &meta);
	mlx_key_hook(meta.mlx, keyhook, &meta);
	mlx_loop(meta.mlx);
	mlx_terminate(meta.mlx);
	return (EXIT_SUCCESS);
}
