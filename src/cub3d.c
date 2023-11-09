/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cub3d.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/07 15:36:26 by jboeve        #+#    #+#                 */
/*   Updated: 2023/11/09 02:41:57 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "meta.h"
#include "MLX42/MLX42.h"
#include "timer.h"


// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static void	fps_hook(void *param)
{
	t_meta			*meta = param;

	if (!(meta->fps_timer.time_func))
		timer_init(&meta->fps_timer, mlx_get_time);
	if (timer_delta(&meta->fps_timer) >= 1)
	{
		printf("FPS: [%u]\n", meta->fps);
		timer_start(&meta->fps_timer);
		meta->fps = 0;
	}
	else
		meta->fps++;
}

int cub3d(int argc, char *argv[])
{
	t_meta	meta;

	UNUSED(argc);
	UNUSED(argv);

	// Zero our struct to prevent garbage data.
	ft_bzero(&meta, sizeof(t_meta));

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
	mlx_loop_hook(meta.mlx, fps_hook, &meta);
	mlx_key_hook(meta.mlx, keyhook, &meta);
	mlx_loop_hook(meta.mlx, game_loop, &meta);
	mlx_loop(meta.mlx);
	mlx_terminate(meta.mlx);
	return (EXIT_SUCCESS);
}
