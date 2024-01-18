/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                           :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:24:47 by yzaim             #+#    #+#             */
/*   Updated: 2024/01/18 10:45:29 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "MLX42/MLX42_Int.h"
#include "meta.h"
#include "parser.h"
#include <stdint.h>


static void	fps_hook(void *param)
{
	t_meta	*meta = param;
	static uint32_t fps = 0;

	if (!(meta->fps_timer.time_func))
		timer_init(&meta->fps_timer, mlx_get_time);
	if (timer_delta(&meta->fps_timer) >= 1)
	{
		meta->fps = fps;
		printf("FPS: [%u]\n", fps);
		timer_start(&meta->fps_timer);
		fps = 0;
	}
	else
		fps++;
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
	meta->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, meta->scene_name, true);
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
		ft_error();
		return (EXIT_FAILURE);
	}

	meta->minimap.info_image = mlx_new_image(meta->mlx, MINIMAP_WIDTH, MINIMAP_INFO_HEIGHT);
	if (!meta->minimap.info_image || (mlx_image_to_window(meta->mlx, meta->minimap.info_image, 0, MINIMAP_HEIGHT) < 0))
	{
		ft_error();
		return (EXIT_FAILURE);
	}

	meta->minimap.ppos_image = mlx_new_image(meta->mlx, 1, 1);
	if (!meta->minimap.ppos_image || (mlx_image_to_window(meta->mlx, meta->minimap.ppos_image, 3, MINIMAP_HEIGHT) < 0))
	{
		ft_error();
		return (EXIT_FAILURE);
	}

	meta->minimap.fps_image = mlx_new_image(meta->mlx, 1, 1);
	if (!meta->minimap.fps_image || (mlx_image_to_window(meta->mlx, meta->minimap.fps_image, 3, MINIMAP_HEIGHT + 16) < 0))
	{
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
	if (set_textures(&meta.attributes))
		return (EXIT_FAILURE);
	printf("Tex_N: %s\n", meta.attributes.n.tex_path);
	printf("Tex_S: %s\n", meta.attributes.s.tex_path);
	printf("Tex_E: %s\n", meta.attributes.e.tex_path);
	printf("Tex_W: %s\n", meta.attributes.w.tex_path);
	
	init_mlx_images(&meta);
	// TODO Error check.
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
