/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cub3d.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/07 15:36:26 by jboeve        #+#    #+#                 */
/*   Updated: 2023/12/15 16:38:07 by joppe         ########   odam.nl         */
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

// change to create a different image for the minimap vs. main viewport
int init_mlx_images(t_meta *meta)
{
	meta->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, true);
	if (!meta->mlx)
	{
		ft_error();
		return EXIT_FAILURE;
	}

	// Create and display the image.
	meta->image = mlx_new_image(meta->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!meta->image || (mlx_image_to_window(meta->mlx, meta->image, 0, 0) < 0))
	{
		ft_error();
		return (EXIT_FAILURE);
	}
	return (0);
}

int	set_textures(t_tex *tex)
{
	tex->n = mlx_load_png("texture_examples/redbrick.png");
	if (tex->n == NULL)
		return (1);
	tex->s = mlx_load_png("texture_examples/redbrick.png");
	if (tex->s == NULL)
		return (1);
	tex->e = mlx_load_png("texture_examples/purplestone.png");
	if (tex->e == NULL)
		return (1);
	tex->w = mlx_load_png("texture_examples/purplestone.png");
	if (tex->w == NULL)
		return (1);
	return (EXIT_SUCCESS);
}

int cub3d(int argc, char **argv)
{
	t_meta	meta;

	if (argc != 2)
		return (pr_err(ARG_ERR));
	ft_bzero(&meta, sizeof(t_meta));
	if (parser(&meta, argv[1]))
		return(meta_free(&meta), EXIT_FAILURE);
	if (set_textures(&meta.tex))
		return (meta_free(&meta), EXIT_FAILURE);
	init_mlx_images(&meta);
	game_init(&meta);
	mlx_loop_hook(meta.mlx, game_loop, &meta);
	mlx_loop_hook(meta.mlx, key_hook, &meta);
	mlx_loop(meta.mlx);
	mlx_terminate(meta.mlx);
	meta_free(&meta);
	return (EXIT_SUCCESS);
}
