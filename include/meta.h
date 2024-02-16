/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   meta.h                                            :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/05 14:01:44 by joppe         #+#    #+#                 */
/*   Updated: 2024/02/16 13:02:30 by joppe         ########   odam.nl         */
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


typedef struct s_meta t_meta;

typedef enum e_cell_type {
	MAP_EMPTY,
	MAP_WALL,
	MAP_SPACE,
	MAP_DOOR_OPEN,
	MAP_DOOR_CLOSED,
}	t_cell_type;

typedef t_cell_type	(t_ray_hitfunc) (const void *p, uint32_t x, uint32_t y);

typedef enum e_element_type {
	INVALID,
	CEIL_FLOOR,
	WALL,
	SPRITE,
	DOOR,
	NEXT_LVL,
}	t_element_type;

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
	// `id` just for debugging.
	uint32_t	id;
	t_vec2d		direction;
	t_vec2d		end;
	t_vec2i		map_pos;
	t_vec2i		texture_point;
	t_vec2i		line_point;
	t_side		hit_side;
	t_cell_type hit_cell;

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
	t_ray 		interact_ray;
	bool 		should_render;
	t_vec2d		cam_plane;
	t_vec2d		position;
	t_vec2d		direction;
	// Sprite stuff.
	int32_t 	*sprite_order; // malloc these based on the sprite count
	double		*sprite_dist;
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
	char			*flag;
	char			*content;
	struct s_flag	*next;
}	t_flag;

typedef struct s_tex {
	char			*tex_path;
	mlx_texture_t	*tex;
}	t_tex;

typedef struct s_sprite {
	t_vec2d			pos;
	t_tex			tex;
} t_sprite;

typedef struct s_door {
	uint32_t	door_count;
	t_tex		tex;
	uint32_t	*idx;
}	t_door;

typedef struct s_attr {
	t_tex		n;	//add bit flag, if tex_path is missing then it means it is a color value
	t_tex		s;
	t_tex		e;
	t_tex		w;
	t_tex		f;
	t_tex		c;
	t_tex		c_alt;
	t_rgba		floor_c;
	t_rgba		ceiling_c;
	uint32_t	sprite_count;
	uint32_t	sprite_arr_index;
	t_sprite	*sprites; // we need to make the sprite count modular
	t_door		doors;
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
	mlx_image_t	*debug_img;
	t_timer 	update_timer;
	t_minimap 	minimap;
	t_timer 	fps_timer;
	uint32_t 	fps;
	t_map		map;
	t_attr		attributes;
	const char	*scene_name;
	t_flag		*elements;
	t_player	player;
	char		*next_level;
	bool 		key_states[MLX_KEY_MENU - MLX_KEY_SPACE];
	bool 		test_ids[WINDOW_WIDTH];
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
void 	player_interact(t_player *p);

// keys.c
void	cursor_hook(double xpos, double ypos, void* param);
void	keys_handle(t_meta *meta, double time_delta);

// render_minimap.c
void 	render_minimap(t_minimap *minimap, const t_map *map, const t_player *p);

// render_viewport.c
void	render_viewport(mlx_image_t *image, t_player *p);

// minimap.c
void 	minimap_update(mlx_image_t *image, t_player *p);

// draw.c
void	draw_rect(mlx_image_t* image, uint32_t x_pos, uint32_t y_pos, uint32_t width, uint32_t height, uint32_t color);
void	draw_line(mlx_image_t *image, t_vec2i start, t_vec2i end, t_rgba c);
void	draw_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color);

// font_renderer.c
const t_font_atlas	*cube_get_font_atlas(t_font_family face);
mlx_image_t			*cube_put_string(mlx_image_t *image, const char *s, const t_font_atlas *atlas);


// keys.c
void		keys_update(mlx_key_data_t keydata, void *param);

// raycaster.c
t_ray		raycaster_cast(t_vec2d pp, t_vec2d dir, t_ray_hitfunc hit, const void *param);

// colors.c
int32_t		set_color(int32_t r, int32_t g, int32_t b, int32_t a);
int32_t		find_wall_color(t_attr atrributes, t_ray *ray, t_vec2i line_points, uint32_t h);
int32_t		find_color(t_rgba rgba);
mlx_texture_t	*get_texture(t_cell_type cell, t_side side, t_attr attributes);

// free.c
void		meta_free(t_meta *meta);
void		free_t_flag_list(t_flag **list);

// set_textures.c
int			set_textures(t_attr *attributes);

//pixel_picker.c
uint32_t	pixel_picker(mlx_texture_t *texture, int32_t x, int32_t y);
void		wall_texture_position(mlx_texture_t *texture, t_ray *ray, t_vec2i line_points, uint32_t h);

// floorcaster.c
t_vray 	floorcaster(t_vec2d pp, t_vec2d dir, t_vec2d cam_plane, uint32_t y);

// sprite.c
int		init_sprites(uint32_t sprite_count, int32_t **sprite_order, double **sprite_dist);
void	sprite_calculate(t_player *p);

// test_utils.c REMOVE LATER

void	print_double_array(char *msg, double *arr, uint32_t size, t_sprite *sp, int32_t *order);
void	print_ints_array(char *msg, int32_t *arr, uint32_t size);
void	print_sprites_array(t_sprite *arr, uint32_t size);
void	print_attributes(t_attr *attributes);
void	print_door_data(t_door doors);
// sprite_utils.c

void	sprite_sort(double *sprite_dist, int32_t *sprite_order, uint32_t sprite_count);


// lexer.c
char 	*extract_file(char *map_file);
int		lex(char *file, t_map *map, t_flag **elements);
int		lexer(t_meta *meta, char *map_file);

// lexer_utils.c

void	print_lexer_map(t_map *map);
void 	print_lexer_elements(t_flag *elements);

// map_lexer.c

bool	nl_only_spaces(char *file);
int		end_of_map(char *file);
void	skip_map_element(char **file, int *skip);
int		input_map_lexer(char *file, t_map *map);
int		map_lex(char **file, t_map *map, int *skip, int mandatory);

// extra_lexer.c

char	*get_title_val(char *file);
int		save_extra_title(t_flag **extras, char **file);
bool	is_valid_extra(char *file);
int		lexer_input_extra(t_flag **extras, char *file, int *skip);



// world.c
void world_interact(t_player *p, t_vec2d map_pos);
bool world_is_interactable(t_cell_type cell);

#endif
