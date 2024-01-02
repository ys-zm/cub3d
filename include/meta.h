/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   meta.h                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/01 20:07:37 by jboeve        #+#    #+#                 */
/*   Updated: 2024/01/02 21:52:00 by joppe         ########   odam.nl         */
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
#include "vector.h"
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

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720 

#define WINDOW_TITLE "Gammoe"

#define TICK_RATE (1.0 / 60.0)

// TODO Move all this stuff to some kind of game.h
#define CELL_WIDTH			64
#define CELL_HEIGHT			64
#define CELL_SIZE 			64

#define PLAYER_MOVE_SPEED   5.0
#define PLAYER_RUN_MODIFIER 2.5
#define PLAYER_ROTATE_SPEED	5.0
#define PLAYER_ROTATE_MODIFIER 2.5


#define PLAYER_MOV_SPEED	0.08

#define COLOR_BACKGROUND	0x111111FF
#define COLOR_PLAYER		0xFFFFFFFF

// #define FOV 0.66
#define FOV 0.85

typedef bool	(t_ray_hitfunc) (void *p, uint32_t x, uint32_t y);
typedef struct s_meta t_meta;

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


typedef enum e_side {
	HIT_NONE,
	HIT_NS,
	HIT_EW,
}	t_side;

typedef struct s_ray {
	t_side	hit_side;
	double	length;
	t_vec2d	direction;
} t_ray;


typedef struct s_player {
	t_meta		*meta;
	t_ray		rays[WINDOW_WIDTH];
	t_vec2d		cam_plane;
	t_vec2d		position;
	t_vec2d		direction;
} t_player;


typedef struct s_map {
	t_cell_type *level;
	uint32_t	width;
	uint32_t	height;
	t_vec2u		player_start;
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
void player_move(t_player *p, t_vec2d transform);
void	player_turn(t_player *p, float radiant);
void	player_raycast(t_player *p);

// keys.c
void	mouse_hook(double xpos, double ypos, void* param);
void	keys_handle(t_meta *meta, double time_delta);

// render.c
void	render_player_viewport(mlx_image_t *image, t_player *p);
void	render_clear_bg(mlx_image_t *image);
void	render_minimap(mlx_image_t *image, t_map *m);

// draw.c
void	draw_rect(mlx_image_t* image, uint32_t x_pos, uint32_t y_pos, uint32_t width, uint32_t height, uint32_t color);
void	draw_line(mlx_image_t *image, t_vec2i start, t_vec2i end, t_rgba c);
void	draw_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color);


// keys.c
void	keys_update(mlx_key_data_t keydata, void *param);

// draw.c
void 	draw_square(mlx_image_t* image, uint32_t x_pos, uint32_t y_pos, uint32_t width, uint32_t height, uint32_t color);
void 	cube_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color);

// raycaster.c
t_ray raycaster_cast(t_meta *meta, t_vec2d pp, t_vec2d dir, t_ray_hitfunc hit);

// colors.c
int32_t		set_color(int32_t r, int32_t g, int32_t b, int32_t a);
int32_t		find_wall_color(t_side side);

// free.c
void		meta_free(t_meta *meta);

#endif
