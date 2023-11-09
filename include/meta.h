/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   meta.h                                             :+:      :+:    :+:   */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/01 20:07:37 by jboeve        #+#    #+#                 */
/*   Updated: 2023/11/08 23:54:38 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef META_H
#define META_H

#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include "timer.h"
#include "MLX42/MLX42.h"

#define UNUSED(x) (void)(x)
#define UNIMPLEMENTED(message) \
	do { \
		fprintf(stderr, "\x1b[0m%s:%d: UNIMPLEMENTED: %s\n", __FILE__, __LINE__, message); \
		exit(1); \
	} while (0)
#define UNREACHABLE(message) \
	do { \
		fprintf(stderr, "\x1b[0m%s:%d: UNREACHABLE: %s\n", __FILE__, __LINE__, message); \
		exit(1); \
	} while (0)

// Window settings
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "Gammoe"

#define TICK_RATE (1.0 / 60.0)

// TODO Move all this stuff to some kind of game.h
#define MAP_WIDTH 			8
#define MAP_HEIGHT			8

#define CELL_WIDTH			64
#define CELL_HEIGHT			64

#define PLAYER_WIDTH		16
#define PLAYER_HEIGHT		16

#define PLAYER_WALK_SPEED	100

#define COLOR_BACKGROUND	0x111111FF
#define COLOR_PLAYER		0xBF00C9FF


typedef union s_rgba
{
	uint32_t	value;
	struct
	{
		uint8_t	a;
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
	};
}	t_rgba;

typedef enum e_cell_type {
    MAP_EMPTY,
    MAP_WALL,
    MAP_SPACE,
}	t_cell_type;

typedef struct s_player {
	float	x;
	float	y;
} t_player;

typedef struct s_meta {
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_timer 	update_timer;
	t_timer 	fps_timer;
	t_player 	player;
	uint32_t 	fps;
}	t_meta;

// cub3d.c
int	cub3d(int argc, char *argv[]);

// game.c
void game_init(t_meta *meta);
void game_loop(void* param);

// player.c
void player_move(t_meta *meta);

// keys.c
void keyhook(mlx_key_data_t keydata, void* param);

// render.c
void render_player(t_meta *meta);
void render_clear_bg(mlx_image_t *image);
void render_map_grid(t_meta *meta);

// draw.c
void draw_square(mlx_image_t* image, uint32_t x_pos, uint32_t y_pos, uint32_t width, uint32_t height, uint32_t color);
void cube_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color);

#endif
