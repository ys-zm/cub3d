/* ************************************************************************** */
/**/
/*   :::::::: */
/*   parser.h  :+::+: */
/*+:+ */
/*   By: jboeve <jboeve@student.codam.nl>+#+  */
/*  +#+   */
/*   Created: 2023/11/01 20:07:37 by jboeve#+##+# */
/*   Updated: 2024/01/02 19:05:30 by joppe ########   odam.nl */
/**/
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

# define TOO_MANY_PLAYERS "Map should not have more than one player position\n"
# define INVALID_CHAR "Map has invalid characters\n"
# define INVALID_WALLS "Map walls are not closed\n"
# define INVALID_EXT "Map extension should be .cub\n"
# define INVALID_FILE "Map file failed to open\n"
# define MALLOC_FAIL "Malloc error\n"
# define WRO_ARGS "Wrong number of arguments\n"
# define OOB_FLOOR "There are inaccessible floors in this map\n"
# define ORDER_OF_ELEMENTS "Error in map file, check that the map element is last and there are no extra characters between elements\n"
# define MISSING_PATH   "Texture path missing\n"
# define DUPLICATES "Make sure you have only and at least one value for each element\n"
# define NO_PLAYER_POS "There is no player position in the map\n"
# define ELEMENT_MISSING "One or more definition of elements is missing\n"
# define NO_MAP "Map element is missing\n"
# define INV_COLOR_CODE "Please check color codes for F and C elements\nRGB values should be between 0-255\n"

# include "meta.h"

typedef enum e_err {
INV_CHAR, 
INV_EXT, 
INV_WALLS,
PLAY_ERR,
INV_FILE,
MALL_ERR,
ARG_ERR,
OUT_OF_BOUNDS,
FILE_ORDER,
M_PATH,
DUP_ELEMENTS,
NO_PLAYER,
MISSING_ELEMENTS,
MISSING_MAP,
COLOR_CODE_WRONG,
}   t_err;

// error.c
int pr_err(t_err type);

// check_map.c
int valid_map_char(char c);
int	player_pos_char(char c);
bool	is_map_chars_valid(char *map);
int 	check_map(t_meta *meta, char *rect);
int		find_index(t_meta *meta, uint32_t x, uint32_t y);


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


#endif
