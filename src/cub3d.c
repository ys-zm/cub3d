/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                           :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:24:47 by yzaim         #+#    #+#                 */
/*   Updated: 2024/03/03 19:24:01 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "meta.h"
#include "error.h"
#include <stdint.h>

static void	fps_hook(void *param)
{
	static uint32_t	fps;
	t_meta			*meta;

	fps = 0;
	meta = param;
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

// change to create a different image for the minimap vs. main viewport
int	init_mlx_images(t_meta *meta)
{
	meta->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, meta->scene_name, true);
	if (!meta->mlx)
		return (pr_err(MLX_ERROR));
	meta->image = mlx_new_image(meta->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!meta->image || (mlx_image_to_window(meta->mlx, meta->image, 0, 0) < 0))
		return (pr_err(MLX_ERROR));
	meta->minimap.minimap_image = mlx_new_image(meta->mlx, MINIMAP_WIDTH, \
												MINIMAP_HEIGHT);
	if (!meta->minimap.minimap_image || (mlx_image_to_window(meta->mlx, \
									meta->minimap.minimap_image, 0, 0) < 0))
		return (pr_err(MLX_ERROR));
	meta->minimap.info_image = mlx_new_image(meta->mlx, MINIMAP_WIDTH, \
											MINIMAP_INFO_HEIGHT);
	if (!meta->minimap.info_image || (mlx_image_to_window(meta->mlx, \
				meta->minimap.info_image, 0, MINIMAP_HEIGHT) < 0))
		return (pr_err(MLX_ERROR));
	meta->minimap.ppos_image = mlx_new_image(meta->mlx, 1, 1);
	if (!meta->minimap.ppos_image || (mlx_image_to_window(meta->mlx, \
			meta->minimap.ppos_image, 3, MINIMAP_HEIGHT) < 0))
		return (pr_err(MLX_ERROR));
	meta->minimap.fps_image = mlx_new_image(meta->mlx, 1, 1);
	if (!meta->minimap.fps_image || (mlx_image_to_window(meta->mlx, \
			meta->minimap.fps_image, 3, MINIMAP_HEIGHT + 16) < 0))
		return (pr_err(MLX_ERROR));
	return (EXIT_SUCCESS);
}

int	init_input(t_meta *meta, char *av)
{
	if (lexer(meta, av))
		return (EXIT_FAILURE);
	if (parser(meta))
		return (meta_free(meta), EXIT_FAILURE);
	if (set_textures(&meta->attributes))
		return (meta_free(meta), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	cub3d(int argc, char **argv)
{
	t_meta	meta;

	if (argc != 2)
		return (pr_err(ARG_ERR));
	ft_bzero(&meta, sizeof(t_meta));
	if (init_input(&meta, argv[1]))
		return (EXIT_FAILURE);
	init_mlx_images(&meta);
	// TODO error handling
	if (game_init(&meta))
		return (meta_free(&meta), EXIT_FAILURE);
	mlx_set_cursor_mode(meta.mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(meta.mlx, game_loop, &meta);
	mlx_loop_hook(meta.mlx, fps_hook, &meta);
	mlx_cursor_hook(meta.mlx, cursor_hook, &meta);
	mlx_loop(meta.mlx);
	mlx_terminate(meta.mlx);
	meta_free(&meta);
	return (EXIT_SUCCESS);
}
