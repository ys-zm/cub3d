/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   meta.h                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/01 20:07:37 by jboeve        #+#    #+#                 */
/*   Updated: 2023/11/13 21:19:38 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef META_H
#define META_H

#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include "timer.h"
#include "vector.h"
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

#define PI 3.1415926535

// Window settings
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "Gammoe"

#define TICK_RATE (1.0 / 60.0)

// TODO Move all this stuff to some kind of game.h
#define CELL_WIDTH			64
#define CELL_HEIGHT			64

#define PLAYER_WIDTH		16
#define PLAYER_HEIGHT		16
#define PLAYER_RAY_COUNT	360
#define PLAYER_WALK_SPEED	15
#define PLAYER_ROTATE_SPEED	5
#define PLAYER_RUN_MODIFIER 2.5

#define COLOR_BACKGROUND	0x111111FF
#define COLOR_PLAYER		0xFFFFFFFF

#define VEC_X 0
#define VEC_Y 1



typedef enum e_cell_type {
    MAP_EMPTY,
    MAP_WALL,
    MAP_SPACE,
}	t_cell_type;



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

typedef struct s_ray {
	t_vec2f start;
	t_vec2f end;
} t_ray;

typedef struct s_meta t_meta;

// NOTE: Maybe switch to double instead of float?
typedef struct s_player {
	t_meta *meta;
	// TODO Have a map_position which will be the position relative to the leftmost square.
	// 		Based on that position we can just `position / CELL_WIDTH` to find the cell position.
	t_vec2i map_cell;
	t_vec2f position;
	t_vec2f direction;
	t_vec2f beam;
	t_ray 	rays[PLAYER_RAY_COUNT];
	float	angle;
} t_player;

typedef struct s_map {
	uint32_t	width;
	uint32_t	height;
	t_cell_type *level;
} t_map;


typedef struct s_meta {
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_timer 	update_timer;
	t_timer 	fps_timer;
	t_player 	player;
	t_map 		map;
	uint32_t 	fps;
}	t_meta;

// cub3d.c
int	cub3d(int argc, char *argv[]);

// game.c
void game_init(t_meta *meta);
void game_loop(void* param);

// player.c
void player_move(t_player *p, t_vec2f transform);
void player_look(t_player *p, double angle);
void player_raycast(t_player *p);

// input.c
void key_hook(mlx_key_data_t keydata, void* param);
void cursor_hook(double xpos, double ypos, void* param);

// render.c
t_vec2i	render_get_draw_offset();
void	render_player(mlx_image_t *image, t_player *p);
void	render_clear_bg(mlx_image_t *image);
void	render_map_grid(mlx_image_t *image, t_map *m);

// map.c
t_cell_type	map_get_cell_type(t_map *m, t_vec2f pos);

// draw.c
void	draw_square(mlx_image_t* image, uint32_t x_pos, uint32_t y_pos, uint32_t width, uint32_t height, uint32_t color);
void	draw_line(mlx_image_t *image, t_vec2i start, t_vec2i end, t_rgba c);
void	draw_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color);

// utils.c
float deg_to_rad(float deg);

// test_utils.c
void	print_vec2f(const char *s, t_vec2f vec);
void	print_vec2i(const char *s, t_vec2i vec);
void	print_cell(t_cell_type cell);

#endif
