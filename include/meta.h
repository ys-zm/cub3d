/* ************************************************************************** */
/**/
/*   :::::::: */
/*   meta.h                                            :+:    :+:             */
/*+:+ */
/*   By: jboeve <jboeve@student.codam.nl>+#+  */
/*  +#+   */
/*   Created: 2023/11/01 20:07:37 by jboeve#+##+# */
/*   Updated: 2024/01/29 15:27:32 by yesimzaim     ########   odam.nl         */
/**/
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
#include <math.h>

#include "timer.h"
#include "libft.h"
#include "vector.h"
#include "get_next_line.h"
#include "MLX42/MLX42.h"

#define UNUSED(x) (void)(x)
#define WARNING(message) \
	do { \
		fprintf(stderr, "\x1b[0m%s:%d: WARNING: %s\n", __FILE__, __LINE__, message); \
	} while (0)

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


// Window
// #define WINDOW_WIDTH 1920
// #define WINDOW_HEIGHT 1080 
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720 

#define BPP 4


// Game
#define TICK_RATE (1.0 / 60.0)

#define PLAYER_MOVE_SPEED   3.5
#define PLAYER_RUN_MODIFIER 2.5
#define PLAYER_ROTATE_SPEED	3.0
#define PLAYER_ROTATE_MODIFIER 2.5

#define MINIMAP_WIDTH				350
#define MINIMAP_HEIGHT				230
#define MINIMAP_INFO_HEIGHT 		50
#define MINIMAP_COLOR_BACKGROUND	0x111111cc
#define MINIMAP_COLOR_BORDER		0x666666ff
#define MINIMAP_COLOR_PLAYER		0xd32a04FF
#define MINIMAP_PLAYER_SIZE 		7
#define MINIMAP_CELL_SIZE 			24

#define VIEWPORT_COLOR_CEILING 		0x000000FF
#define VIEWPORT_COLOR_FLOOR 		0xFFFFFFFF
#define VIEWPORT_COLOR_WALL_NS		0x4B0082FF
#define VIEWPORT_COLOR_WALL_EW		0x8A30E2FF

#define FOV 0.85

#define SPRITE_COUNT 2

typedef bool	(t_ray_hitfunc) (const void *p, uint32_t x, uint32_t y);

typedef struct s_meta t_meta;

typedef enum e_cell_type {
MAP_EMPTY,
MAP_WALL,
MAP_SPACE,
MAP_DOOR
}	t_cell_type;

typedef enum e_font_family {
	FONT_DEJAVU_14,
	FONT_MLX,
	FONT_COMICSANS_13,
	FONT_COUNT,
}	t_font_family;

typedef struct s_font_atlas
{
	unsigned int 	 width;
	unsigned int 	 height;
	unsigned int 	 font_w;
	unsigned int 	 font_h;
	unsigned int 	 bpp;
	char			*pixels;
} t_font_atlas;


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
	SIDE_N = 0, 
	SIDE_S = 1,
	SIDE_E = 2,
	SIDE_W = 3,
}	t_side;

typedef struct s_ray {
	t_vec2d		direction;
	t_vec2d		end;
	t_vec2i		map_pos;
	t_vec2i		texture_point;
	t_vec2i		line_point;
	t_side		hit_side;

	double		line_height;
	double		length;
	double 		wall_x;
	double		texture_position;
	double		step;
} t_ray;

typedef struct s_vray {
	t_vec2d		floor;
	t_vec2d		step;
}	t_vray;

typedef struct s_player {
	t_meta		*meta;
	t_ray		rays[WINDOW_WIDTH];
	t_vray		vrays[WINDOW_HEIGHT];
	bool 		should_render;
	t_vec2d		cam_plane;
	t_vec2d		position;
	t_vec2d		direction;
	// Sprite stuff.
	int32_t 	sprite_order[SPRITE_COUNT];
	double		sprite_dist[SPRITE_COUNT];
	double 		z_buffer[WINDOW_WIDTH];
} t_player;


typedef struct s_map {
	char		*map_element;
	t_cell_type *level;
	uint32_t	width;
	uint32_t	height;
	t_vec2u		player_start;
	char		player_start_dir;
}	t_map;

typedef struct s_flag
{
	char	*flag;
	char	*content;
	struct s_flag	*next;
}	t_flag;


typedef struct s_lex {
	t_flag	n;
	t_flag	s;
	t_flag	e;
	t_flag	w;
	t_flag	c;
	t_flag	f;
}	t_lex;

typedef struct s_sprite {
	t_vec2d			pos;
	mlx_texture_t	*tex;
} t_sprite;

typedef struct s_tex {
	char			*tex_path;
	mlx_texture_t	*tex;
}	t_tex;


typedef struct s_attr {
	t_tex	n;	//add bit flag, if tex_path is missing then it means it is a color value
	t_tex	s;
	t_tex	e;
	t_tex	w;
	t_tex	f;
	t_tex	c;
	t_tex	c_alt;
	t_rgba	floor_c;
	t_rgba	ceiling_c;
	t_sprite sprites[SPRITE_COUNT];
}	t_attr;

typedef struct s_minimap {
	mlx_image_t	*minimap_image;
	mlx_image_t	*ppos_image;
	mlx_image_t	*fps_image;
	mlx_image_t	*info_image;
}	t_minimap;

typedef struct s_meta {
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_timer 	update_timer;
	t_minimap 	minimap;
	t_timer 	fps_timer;
	t_player	player;
	uint32_t 	fps;
	t_map		map;
	t_attr		attributes;
	const char	*scene_name;
	char		*map_element;
	t_lex		lexer;
	t_flag		*extras;
}	t_meta;


// cub3d.c
int		cub3d(int argc, char *argv[]);

// game.c
void	game_init(t_meta *meta);
void	game_loop(void* param);

// player.c
void	player_move(t_player *p, t_vec2d transform);
void	player_turn(t_player *p, float radiant);
void	player_raycast(t_player *p);

// keys.c
void	cursor_hook(double xpos, double ypos, void* param);
void	keys_handle(t_meta *meta, double time_delta);

// render_minimap.c
void render_minimap(t_minimap *minimap, const t_map *map, const t_player *p);

// render_viewport.c
void	render_viewport(mlx_image_t *image, t_player *p);

// minimap.c
void minimap_update(mlx_image_t *image, t_player *p);

// draw.c
void	draw_rect(mlx_image_t* image, uint32_t x_pos, uint32_t y_pos, uint32_t width, uint32_t height, uint32_t color);
void	draw_line(mlx_image_t *image, t_vec2i start, t_vec2i end, t_rgba c);
void	draw_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color);

// font_renderer.c
const t_font_atlas	*cube_get_font_atlas(t_font_family face);
mlx_image_t			*cube_put_string(mlx_image_t *image, const char *s, const t_font_atlas *atlas);


// keys.c
void	keys_update(mlx_key_data_t keydata, void *param);

// raycaster.c
t_ray		raycaster_cast(t_vec2d pp, t_vec2d dir, t_ray_hitfunc hit, const void *param);

// colors.c
int32_t		set_color(int32_t r, int32_t g, int32_t b, int32_t a);
int32_t	find_wall_color(t_attr atrributes, t_ray *ray, t_vec2i line_points, uint32_t h);
int32_t		find_color(t_rgba rgba);

// free.c
void		meta_free(t_meta *meta);

// set_textures.c
int		set_textures(t_attr *attributes);

//pixel_picker.c
uint32_t	pixel_picker(mlx_texture_t *texture, int32_t x, int32_t y);
void	wall_texture_position(mlx_texture_t *texture, t_ray *ray, t_vec2i line_points, uint32_t h);

// floorcaster.c
t_vray floorcaster(t_vec2d pp, t_vec2d dir, t_vec2d cam_plane, uint32_t y);

// sprite.c
void	init_sprites(t_sprite *sprites);
void	sprite_calculate(t_player *p);

// test_utils.c REMOVE LATER

void	print_double_array(char *msg, double *arr, uint32_t size);
void	print_ints_array(char *msg, int32_t *arr, uint32_t size);

// sprite_utils.c

void	sprite_sort(double *sprite_dist, int32_t *sprite_order);


// lexer.c

int	lexer(t_meta *meta, char *map_file);

// lexer_utils.c

void	print_lexer_mandatory(t_lex *lexer);
void	print_lexer_map(t_map *map);
void	print_lexer_extras(t_flag *extras);

// parser.c


#endif
