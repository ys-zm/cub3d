/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   meta.h                                             :+:      :+:    :+:   */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/01 20:07:37 by jboeve        #+#    #+#                 */
/*   Updated: 2023/11/09 18:54:26 by yzaim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef META_H
#define META_H

#include <inttypes.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "timer.h"
#include "libft.h"
#include "parser.h"
#include "get_next_line.h"
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
// Tick rate for the game logic.
#define TICK_RATE (1.0f / 20.0f)

// TODO Move all this stuff to some kind of game.h
#define MAP_WIDTH 			8
#define MAP_HEIGHT			8

#define CELL_WIDTH			64
#define CELL_HEIGHT			64

#define PLAYER_WIDTH		16
#define PLAYER_HEIGHT		16

#define PLAYER_WALK_SPEED	10

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
	uint32_t	x;
	uint32_t	y;
	uint32_t	start_x;
	uint32_t	start_y;
} t_player;

typedef struct s_map {
	t_cell_type *arr;
	uint32_t	width;
	uint32_t	height;
}	t_map;

typedef struct s_tex {
	char 	*no;
	char 	*so;
	char 	*we;
	char 	*ea;
	t_rgba	floor_c;
	t_rgba	ceiling_c;
}	t_tex;

typedef struct s_meta {
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_timer 	tick_timer;
	t_timer 	fps_timer;
	t_player 	player;
	uint32_t 	fps;
	t_map		map;
	t_tex		tex;
	char		*map_file;
}	t_meta;

// cub3d.c
int		cub3d(int argc, char *argv[]);

// game.c
void 	game_init(t_meta *meta);
void 	game_loop(void* param);

// player.c
void 	player_move(t_meta *meta);

// keys.c
void 	keyhook(mlx_key_data_t keydata, void* param);

// render.c
void 	render_player(t_meta *meta);
void 	render_clear_bg(mlx_image_t *image);
void 	render_map_grid(t_meta *meta);

// draw.c
void 	draw_square(mlx_image_t* image, uint32_t x_pos, uint32_t y_pos, uint32_t width, uint32_t height, uint32_t color);
void 	cube_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color);

// parser.c
int 	parser(t_meta *meta, char *map_file);

// check_map.c
int 	check_map(t_meta *meta, char *rect);
int		find_index(t_meta *meta, uint32_t y, uint32_t x);

// free.c
void 	meta_free(t_meta *meta);

// parse_elements.c
void	skip_line(char **file);
void	skip_spaces(char **file);
int		input_texture(t_tex *tex, char *file);
int		input_colour(t_tex *tex, char *file);
int		save_elements(t_tex *tex, char *file);
int 	parse_elements(t_meta *meta, char *file);

// check_textures.c
bool	is_valid_element(char *file);
bool	only_spaces(char *file);
bool	elements_order(char *file);
bool	is_duplicate(char *file);

// input_map.c
bool	is_map_line(char *file);
int		input_map(t_meta *meta, char *file);

// parse_textures.c
void	get_colour_value(char *file, t_rgba *col);
char	*get_tex_val(char *file);
bool	is_texture(char *file);
bool	is_colour(char *file);

#endif
