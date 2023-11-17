/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/07 15:36:26 by jboeve        #+#    #+#                 */
/*   Updated: 2023/11/09 18:44:40 by yzaim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"

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

void leaks(void)
{
	system("leaks -q app");
}

void init(t_meta *meta)
{
	meta->tex = malloc(sizeof(t_tex) * 1);
	meta->tex->no = NULL;
	meta->tex->so = NULL;
	meta->tex->ea = NULL;
	meta->tex->we = NULL;
}

int cub3d(int argc, char *argv[])
{
	t_meta	meta;

	// UNUSED(argv);
	// atexit(&leaks);
	if (argc != 2)
		return (pr_err(ARG_ERR));
	// Zero our struct to prevent garbage data.
	ft_bzero(&meta, sizeof(t_meta));
	init(&meta);
	if (parser(&meta, argv[1]))
		return(meta_free(&meta), 1);
	meta_free(&meta);
	return (0);
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
	exit(0);
	mlx_loop_hook(meta.mlx, fps_hook, &meta);
	mlx_key_hook(meta.mlx, keyhook, &meta);
	mlx_loop_hook(meta.mlx, game_loop, &meta);
	mlx_loop(meta.mlx);
	mlx_terminate(meta.mlx);
	return (EXIT_SUCCESS);
}
