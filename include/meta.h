/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   meta.h                                            :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/05 14:01:44 by joppe         #+#    #+#                 */
/*   Updated: 2024/03/25 14:49:36 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef META_H
# define META_H

# include <inttypes.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <limits.h>
# include <math.h>

# include "timer.h"
# include "libft.h"
# include "vector.h"
# include "get_next_line.h"
# include "MLX42/MLX42.h"

# define PI 3.1415926535

// Window
// # define WINDOW_WIDTH				1920
// # define WINDOW_HEIGHT				1080 
# define WINDOW_WIDTH				1280
# define WINDOW_HEIGHT				720 
# define BPP						4

// Game
# define TICK_RATE					0.016666

# define PLAYER_MOVE_SPEED  		3.5
# define PLAYER_RUN_MODIFIER 		2.5
# define PLAYER_ROTATE_SPEED		3.0
# define PLAYER_ROTATE_MODIFIER		2.5

# define MINIMAP_WIDTH				350
# define MINIMAP_HEIGHT				230
# define MINIMAP_INFO_HEIGHT 		50
# define MINIMAP_COLOR_BACKGROUND	0x111111cc
# define MINIMAP_COLOR_BORDER		0x666666ff
# define MINIMAP_COLOR_PLAYER		0xd32a04FF
# define MINIMAP_PLAYER_SIZE 		7
# define MINIMAP_DEFAULT_ZOOM 		24
# define MINIMAP_ZOOM_MOD 			2
# define VIEWPORT_COLOR_CEILING		0x000000FF
# define VIEWPORT_COLOR_FLOOR		0xFFFFFFFF
# define VIEWPORT_COLOR_WALL_NS		0x4B0082FF
# define VIEWPORT_COLOR_WALL_EW		0x8A30E2FF

# define FOV 0.85

typedef enum e_cell_type
{
	MAP_EMPTY,
	MAP_WALL,
	MAP_SPACE,
	MAP_DOOR_OPEN,
	MAP_DOOR_CLOSED,
}	t_cell_type;

typedef struct s_meta	t_meta;
typedef					t_cell_type	(t_ray_hitfunc) (const void *p, \
						uint32_t x, uint32_t y);

typedef enum e_element_type
{
	INVALID,
	CEIL_FLOOR,
	WALL,
	SPRITE,
	DOOR,
	NEXT_LVL,
}	t_element_type;

typedef enum e_font_family
{
	FONT_DEJAVU_14,
	FONT_MLX,
	FONT_COMICSANS_13,
	FONT_COUNT,
}	t_font_family;

typedef struct s_font_atlas
{
	unsigned int	width;
	unsigned int	height;
	unsigned int	font_w;
	unsigned int	font_h;
	unsigned int	bpp;
	char			*pixels;
}	t_font_atlas;

typedef union s_rgba
{
	uint32_t	value;
	struct
	{
		uint8_t	r;
		uint8_t	g;
		uint8_t	b;
		uint8_t	a;
	};
}	t_rgba;

typedef enum e_side
{
	SIDE_N = 0,
	SIDE_S = 1,
	SIDE_E = 2,
	SIDE_W = 3,
}	t_side;

typedef struct s_ray
{
	t_vec2d		direction;
	t_vec2d		end;
	t_vec2i		map_pos;
	t_vec2i		texture_point;
	t_vec2i		line_point;
	t_side		hit_side;
	t_cell_type	hit_cell;
	double		line_height;
	double		length;
	double		wall_x;
	double		texture_position;
	double		step;
}	t_ray;

typedef struct s_vray
{
	t_vec2d		floor;
	t_vec2d		step;
}	t_vray;

typedef struct s_player
{
	t_meta		*meta;
	t_ray		hrays[WINDOW_WIDTH];
	t_vray		vrays[WINDOW_HEIGHT];
	t_ray		interact_ray;
	bool		should_render;
	t_vec2d		cam_plane;
	t_vec2d		position;
	t_vec2d		direction;
	int32_t		*sprite_order;
	double		*sprite_dist;
	double		z_buffer[WINDOW_WIDTH];
}	t_player;

typedef struct s_map
{
	char		*map_element;
	t_cell_type	*level;
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

typedef struct s_tex
{
	char			*tex_path;
	mlx_texture_t	*tex;
}	t_tex;

typedef struct s_sprite
{
	t_vec2d			pos;
	t_tex			tex;
	int32_t			height;
	int32_t			width;
	int32_t			screen_x;
	t_vec2d			transform;
}	t_sprite;

typedef struct s_door
{
	uint32_t	door_count;
	t_tex		tex;
	uint32_t	*idx;
}	t_door;

typedef struct s_attr
{
	t_tex		n;
	t_tex		s;
	t_tex		e;
	t_tex		w;
	t_tex		f;
	t_tex		c;
	t_tex		c_alt;
	t_rgba		floor_c;
	t_rgba		ceiling_c;
	t_rgba		ceil_alt_c;
	uint32_t	sprite_count;
	uint32_t	sprite_arr_index;
	t_sprite	*sprites;
	t_door		doors;
}	t_attr;

typedef struct s_minimap
{
	mlx_image_t	*minimap_image;
	mlx_image_t	*ppos_image;
	mlx_image_t	*fps_image;
	mlx_image_t	*info_image;
	size_t		tile_size;
}	t_minimap;

typedef struct s_meta
{
	uint32_t	fps;
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_timer		update_timer;
	t_minimap	minimap;
	t_timer		fps_timer;
	t_map		map;
	t_attr		attributes;
	const char	*scene_name;
	t_flag		*elements;
	t_player	player;
	char		*next_level;
	bool		key_states[MLX_KEY_MENU - MLX_KEY_SPACE];
}	t_meta;

// cub3d.c
int					cub3d(int argc, char *argv[]);

// set_textures.c
int					set_textures(t_attr *attributes);

/* GAME */

// game.c
int					game_init(t_meta *meta);
void				game_loop(void *param);

// game_init.c
void				set_player_start_position(t_player *p, char dir);

// player.c
t_cell_type			bound_check(const void *param, uint32_t x, uint32_t y);
void				player_move(t_player *p, t_vec2d transform);
void				player_turn(t_player *p, float radiant);
void				player_raycast(t_player *p);
void				player_interact(t_player *p);

// keys.c
void				cursor_hook(double xpos, double ypos, void *param);
void				keys_handle(t_meta *meta, double time_delta);

// render_minimap.c
void				render_minimap(t_minimap *minimap, const t_map *map, \
					const t_player *p);

// render_viewport.c
void				render_viewport(mlx_image_t *image, t_player *p);

// minimap.c
void				minimap_update(mlx_image_t *image, t_player *p);

// draw.c
void				draw_rect(mlx_image_t *image, t_vec2u pos, t_vec2u size, \
					uint32_t color);
void				draw_line(mlx_image_t *image, t_vec2i start, t_vec2i end, \
					t_rgba c);
void				draw_put_pixel(mlx_image_t *image, uint32_t x, uint32_t y, \
					uint32_t color);

// font_renderer.c
const t_font_atlas	*cube_get_font_atlas(t_font_family face);
mlx_image_t			*cube_put_string(mlx_image_t *image, const char *s, \
					const t_font_atlas *atlas);

// keys.c
void				keys_update(mlx_key_data_t keydata, void *param);

// raycaster.c
t_ray				raycaster_cast(t_vec2d pp, t_vec2d dir, \
					t_ray_hitfunc hit, const void *param);

// colors.c
int32_t				set_color(int32_t r, int32_t g, int32_t b, int32_t a);
int32_t				find_wall_color(t_attr atrributes, t_ray *ray, \
					t_vec2i line_points, uint32_t h);
int32_t				find_color(t_rgba rgba);
mlx_texture_t		*get_texture(t_cell_type cell, t_side side, \
					t_attr attributes);

// free.c
void				meta_free(t_meta *meta);
void				free_t_flag_list(t_flag **list);

//pixel_picker.c
uint32_t			pixel_picker(mlx_texture_t *texture, int32_t x, int32_t y);
void				wall_texture_position(mlx_texture_t *texture, t_ray *ray, \
					t_vec2i line_points, uint32_t h);

// floorcaster.c
t_vray				floorcaster(t_vec2d pp, t_vec2d dir, t_vec2d cam_plane, \
					uint32_t y);

// sprite.c
int					init_sprites(uint32_t sprite_count, \
					int32_t **sprite_order, double **sprite_dist);
void				sprite_calculate(t_player *p);

// sprite_utils.c
void				sprite_sort(double *sprite_dist, int32_t *sprite_order, \
					uint32_t sprite_count);

// sort_utils.c
void				swap_doubles(double *a, double *b);
void				swap_ints(int32_t *a, int32_t *b);

// sprite_parser.c
int					input_sprite_data(t_sprite **sprites_array, \
					uint32_t *i, char *content);
uint32_t			count_sprites(t_flag *elements);
int					set_up_sprites(t_meta *meta);
bool				valid_sprite_content(char *content);

// map_parser.c
t_cell_type			find_enum_value(char c);
bool				save_map(t_meta *meta, char *rect);

// map_checker.c
bool				is_map_chars_valid(char *map);
int					flood_fill(t_meta *meta, char *map, int x, int y);
bool				save_start_pos(t_meta *meta, char *map);
bool				is_floor_exposed(t_meta *meta, char *map);
int					check_map(t_meta *meta, char *rect);

// door_checker.c
bool				check_valid_doors(t_meta *meta, char *map);

// map_parser.c
t_cell_type			find_enum_value(char c);
bool				save_map(t_meta *meta, char *rect);

// parser.c
char				*file_to_string(int fd);
char				*read_file(int fd);
int					map_extension(char *file);
int					parser(t_meta *meta);

// parse_map.c
bool				is_map_line(char *file);

// parse_elements.c
int					input_texture_path(t_attr *attributes, char *flag, \
					char *content);
int					input_colour(t_attr *attributes, char *flag, \
					char *content);
int					save_elements(t_attr *attributes, char *file);
int					parse_elements(t_meta *meta);

// check_colors.c
bool				get_colour_value(char *content, t_rgba *col);

// check_elements.c
bool				is_valid_element(char *file);
bool				only_spaces(char *file);
bool				is_map_element(char *file);
bool				check_missing(int *found);
bool				is_missing(char *file);
bool				is_duplicate(char *file);

// parse_textures.c
char				*get_tex_val(char *file);
bool				is_wall(char *file);
bool				is_floor_or_ceiling(char *file);

// skip_utils.c
void				skip_line(char **file, int to_skip);
void				skip_spaces(char **file);
void				skip_digits(char **file);
int					valid_map_char(char c);
int					player_pos_char(char c);

// map_access_utils.c
uint32_t			find_width(char *map);
uint32_t			find_height(char *map);
char				*make_rect(char *map, uint32_t w, uint32_t h);
int					find_index(t_meta *meta, uint32_t x, uint32_t y);
bool				is_path(char *str);

// double_utils.c
bool				is_double(char *s);
double				ft_atod(char *s);

// door_parser.c
uint32_t			count_doors(t_cell_type *map, uint32_t w, uint32_t h);
int					set_doors(t_door *doors, t_map map);
int					input_path(char **path, char *content);

// lexer.c
int					lexer(t_meta *meta, char *map_file);

// map_lexer.c
bool				nl_only_spaces(char *file);
int					end_of_map(char *file);
void				skip_map_element(char **file, int *skip);
int					input_map_lexer(char *file, t_map *map);
int					map_lex(char **file, t_map *map, int *skip, int mandatory);

// lexer_utils.c
char				*get_val(char *file);
char				*get_key(char *file);
bool				is_valid_key(t_flag *elements, t_flag *new_node, \
					int *mandatory);
char				*extract_file(char *map_file);

// map_utils.c
int					create_rectangle_map_element(t_meta *meta);
void				save_map_dimensions(char *map_file, uint32_t *width, \
					uint32_t *height);

// draw_func.c
void				draw_column(t_meta *meta, t_ray *ray, uint32_t col, \
					uint32_t h);
void				draw_floor(mlx_image_t *image, t_vray *vray, \
					t_attr *attributes, t_vec2i pos);
void				draw_ceil(mlx_image_t *image, t_vray *vray, \
					t_attr *attributes, t_vec2i pos);

// sprite_render.c
void				draw_sprite(t_player *p, t_vec2i draw_start, \
					t_vec2i draw_end, uint32_t i);

// sprite_calc.c
t_vec2i				calc_draw_start(t_player *p, t_sprite sp);
t_vec2i				calc_draw_end(t_player *p, t_sprite sp);
t_vec2d				calc_transform(t_player *p, t_vec2d pos);

// world.c
void				world_interact(t_player *p, t_vec2d map_pos);
bool				world_is_interactable(t_cell_type cell);

#endif
