/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cub3d.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/07 15:36:26 by jboeve        #+#    #+#                 */
/*   Updated: 2023/11/12 20:30:33 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"


// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}


void leaks(void)
{
	system("leaks -q app");
}

int cub3d(int argc, char **argv)
{
	t_meta	meta;

	// UNUSED(argv);
	if (argc != 2)
		return (pr_err(ARG_ERR));
	// Zero our struct to prevent garbage data.
	ft_bzero(&meta, sizeof(t_meta));
	if (parser(&meta, argv[1]))
		return(meta_free(&meta), 1);
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
	mlx_key_hook(meta.mlx, keys_update, &meta);
	mlx_loop(meta.mlx);
	mlx_terminate(meta.mlx);
	meta_free(&meta);
	return (EXIT_SUCCESS);
}
