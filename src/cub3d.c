/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cub3d.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/07 15:36:26 by jboeve        #+#    #+#                 */
/*   Updated: 2024/01/04 15:33:01 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "meta.h"
#include "parser.h"


static void	fps_hook(void *param)
{
	t_meta	*meta = param;

	if (!(meta->fps_timer.time_func))
		timer_init(&meta->fps_timer, mlx_get_time);
	if (timer_delta(&meta->fps_timer) >= 1)
	{
		if (meta->fps)
			printf("FPS: [%u]\n", meta->fps);
		timer_start(&meta->fps_timer);
		meta->fps = 0;
	}
	else
		meta->fps++;
}


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

	meta->image = mlx_new_image(meta->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!meta->image || (mlx_image_to_window(meta->mlx, meta->image, 0, 0) < 0))
	{
		ft_error();
		return (EXIT_FAILURE);
	}
	meta->minimap.minimap_image = mlx_new_image(meta->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	if (!meta->minimap.minimap_image || (mlx_image_to_window(meta->mlx, meta->minimap.minimap_image, 0, 0) < 0))
	{
		mlx_delete_image(meta->mlx, meta->minimap.minimap_image);
		ft_error();
		return (EXIT_FAILURE);
	}

	meta->minimap.info_image = mlx_new_image(meta->mlx, MINIMAP_WIDTH, MINIMAP_INFO_HEIGHT);
	if (!meta->minimap.info_image || (mlx_image_to_window(meta->mlx, meta->minimap.info_image, 0, MINIMAP_HEIGHT) < 0))
	{
		mlx_delete_image(meta->mlx, meta->image);
		mlx_delete_image(meta->mlx, meta->minimap.minimap_image);
		ft_error();
		return (EXIT_FAILURE);
	}

	meta->test_image = mlx_new_image(meta->mlx, 512, 512);
	if (!meta->test_image || (mlx_image_to_window(meta->mlx, meta->test_image, WINDOW_WIDTH / 2 - 100 , WINDOW_HEIGHT / 2 - 100) < 0))
	{
		mlx_delete_image(meta->mlx, meta->image);
		mlx_delete_image(meta->mlx, meta->minimap.minimap_image);
		ft_error();
		return (EXIT_FAILURE);
	}


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
	// TODO Error check.
	init_mlx_images(&meta);
	game_init(&meta);
	mlx_set_cursor_mode(meta.mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(meta.mlx, game_loop, &meta);
	mlx_loop_hook(meta.mlx, fps_hook, &meta);
	mlx_cursor_hook(meta.mlx, cursor_hook, &meta);
	mlx_loop(meta.mlx);
	mlx_terminate(meta.mlx);
	meta_free(&meta);
	return (EXIT_SUCCESS);
}
