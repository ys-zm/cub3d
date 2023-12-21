/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   meta.h                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/01 20:07:37 by jboeve        #+#    #+#                 */
/*   Updated: 2023/12/21 01:07:56 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef META_H
#define META_H

#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <limits.h>

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

#define PI 3.1415926535

// Window settings
// #define WINDOW_WIDTH 1920
// #define WINDOW_HEIGHT 1080 

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 480 

#define WINDOW_TITLE "Gammoe"

#define PLAYER_VIEWPORT_X 720
#define PLAYER_VIEWPORT_Y 512
#define PLAYER_VIEWPORT_WALL_WIDTH 8

#define TICK_RATE (1.0 / 60.0)

// TODO Move all this stuff to some kind of game.h
#define CELL_WIDTH			64
#define CELL_HEIGHT			64
#define CELL_SIZE 			64

#define PLAYER_WIDTH		16
#define PLAYER_HEIGHT		16
#define PLAYER_RAY_COUNT	90
#define PLAYER_WALK_SPEED	15
#define PLAYER_MOVE_SPEED   5.0f
#define PLAYER_RUN_MODIFIER 2.5

#define PLAYER_MOV_SPEED	0.08
#define PLAYER_ROTATE_SPEED	0.05

#define COLOR_BACKGROUND	0x111111FF
#define COLOR_PLAYER		0xFFFFFFFF

#define FOV .66

typedef bool	(t_ray_hit_check) (void *p, int32_t x, int32_t y);
typedef struct s_meta t_meta;

typedef enum e_cell_type {
    MAP_EMPTY,
    MAP_WALL,
    MAP_SPACE,
}	t_cell_type;

typedef enum e_side {
	HIT_NS,
	HIT_EW,
}	t_side;

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

typedef struct s_vec2d {
	double	x;
	double	y;
}	t_vec2d;

typedef struct s_vec2i {
	int32_t	x;
	int32_t	y;
}	t_vec2i;

typedef struct s_vec2u {
	uint32_t	x;
	uint32_t	y;
}	t_vec2u;

typedef struct s_screen {
	uint32_t	w;
	uint32_t	h;
}	t_screen;


/*
@param side_distance: length of ray from current position to next x or y-side
@param delta_distance: length of ray from one x or y-side to next x or y-side
@param step: what direction to step in x or y-direction (either +1 or -1)
@param hit: was there a wall hit?
@param side: was a NS or EW wall hit?
@param perp_wall_distance: distance of perpendicular ray (Euclidean distance would give fisheye effect!)
*/
typedef struct s_ray_data {
	long		line_height;
	double		perp_wall_distance;

	uint32_t	start;
	uint32_t	end;

	t_vec2d		ray_direction;
	t_vec2d		side_distance;
	t_vec2d		delta_distance;
	
	t_vec2d		map_pos;
	t_vec2d		step;
	t_side		side;
	bool 		hit;

	t_vec2d		plane;
	double		camera_x;
} t_ray_data;

typedef struct s_meta t_meta;

typedef struct s_player {
	t_meta		*meta;
	t_vec2d		position;
	t_vec2d		direction;
	t_ray_data	data;
} t_player;


typedef struct s_map {
	t_cell_type *level;
	uint32_t	width;
	uint32_t	height;
	t_vec2u		player_start;
	uint32_t 	player_start_x;
	uint32_t 	player_start_y;
	char		player_start_dir;
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
	t_timer 	update_timer;
	t_timer 	fps_timer;
	t_player	player;
	uint32_t 	fps;
	t_map		map;
	t_tex		tex;
	char		*map_file;
}	t_meta;


// cub3d.c
int		cub3d(int argc, char *argv[]);

// game.c
void	game_init(t_meta *meta);
void	game_loop(void* param);

// player.c
void player_move(t_meta *meta, t_vec2d transform);
bool	if_hits_wall(t_meta *meta, uint32_t x, uint32_t y);
void	player_move_up(t_meta *meta);
void	player_move_down(t_meta *meta);
void	player_move_left(t_meta *meta);
void	player_move_right(t_meta *meta);
void	player_turn(t_meta *meta, double radiant);

// keys.c
void	keys_handle(t_meta *meta, double time_delta);

// render.c
void	render_player_viewport(mlx_image_t *image, t_player *p);
void	render_clear_bg(mlx_image_t *image);
void	render_minimap(mlx_image_t *image, t_map *m);

// map.c
t_cell_type	map_get_cell_type(t_map *m, t_vec2d pos);

// draw.c
void	draw_rect(mlx_image_t* image, uint32_t x_pos, uint32_t y_pos, uint32_t width, uint32_t height, uint32_t color);
void	draw_line(mlx_image_t *image, t_vec2i start, t_vec2i end, t_rgba c);
void	draw_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color);

// test_utils.c
void	print_cell(t_cell_type cell);
void 	game_init(t_meta *meta);
void 	game_loop(void* param);

// keys.c
void	keys_update(mlx_key_data_t keydata, void *param);

// draw.c
void 	draw_square(mlx_image_t* image, uint32_t x_pos, uint32_t y_pos, uint32_t width, uint32_t height, uint32_t color);
void 	cube_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color);

// check_map.c
int 	check_map(t_meta *meta, char *rect);
int		find_index(t_meta *meta, uint32_t x, uint32_t y);

// raycaster.c
void	calculate_delta_dist(t_player *player);
void	calculate_side_distance(t_player *player);
void	dda_algorithm(t_meta *meta);
void	calculate_line_height(t_ray_data *data, int h);
void	calculate_draw_start_and_end(t_meta *meta, uint32_t h);
void	draw_column(t_meta *meta, uint32_t col, uint32_t h);

// PARSER

// parser.c
char	*read_file(int fd);
int		map_ext(char *file);
int 	parser(t_meta *meta, char *map_file);

// parse_map.c
bool	is_map_line(char *file);
int		input_map(t_meta *meta, char *file);

// parse_elements.c
int		input_texture(t_tex *tex, char *file);
int		input_colour(t_tex *tex, char *file);
int		save_elements(t_tex *tex, char *file);
int 	parse_elements(t_meta *meta, char *file);

// check_colors.c
bool	valid_rgb_value(char *file);
bool	is_valid_color(char *file);
bool	colors_valid(char *file);

// check_elements.c
bool	is_valid_element(char *file);
bool	only_spaces(char *file);
bool	is_map_element(char *file);
bool	elements_order(char *file);
bool	check_missing(int *found);
bool	is_missing(char *file);
bool	is_duplicate(char *file);

// check_map.c
bool	is_map_chars_valid(char *map);
int		flood_fill(t_meta *meta, char *map, int x, int y);
bool	save_start_pos(t_meta *meta, char *map);
bool	is_floor_exposed(t_meta *meta, char *map);

// parse_textures.c
void	get_colour_value(char *file, t_rgba *col);
char	*get_tex_val(char *file);
bool	is_texture(char *file);
bool	is_colour(char *file);

// utils_one.c
void	skip_line(char **file);
void	skip_spaces(char **file);
void	skip_digits(char **file);
int		valid_map_char(char c);
int		player_pos_char(char c);

// utils_two.c
uint32_t	find_width(char *map);
uint32_t	find_height(char *map);
char		*make_rect(char *map, uint32_t w, uint32_t h);

// vec2d_utils.c
void		print_vec2d(char *str, t_vec2d vector);
t_vec2d		vec2d_add(t_vec2d v1, t_vec2d v2);
t_vec2d		vec2d_scalar_product(t_vec2d vec, double scalar);
t_vec2d		vec2d_rotate(t_vec2d old, double radiant);
t_vec2d		vec2u_to_vec2d(t_vec2u v);
double		deg_to_rad(float deg);


// test_utils.c
void		print_map(char *map, uint32_t w, uint32_t h);

// colors.c
int32_t		set_color(int32_t r, int32_t g, int32_t b, int32_t a);
int32_t		find_wall_color(t_side side);

// free.c
void		meta_free(t_meta *meta);

#endif
