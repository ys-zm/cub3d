/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   logging.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <yzaim@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 17:24:48 by yzaim         #+#    #+#                 */
/*   Updated: 2024/03/04 17:25:20 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGING_H
# define LOGGING_H

# define TOO_MANY_PLAYERS "Map should not have more than one player position\n"
# define INVALID_CHAR "Map has invalid characters\n"
# define INVALID_WALLS "Map walls are not closed\n"
# define INVALID_EXT "Map extension should be .cub\n"
# define INVALID_FILE "Map file failed to open\n"
# define MALLOC_FAIL "Malloc error\n"
# define WRO_ARGS "Wrong number of arguments\n"
# define OOB_FLOOR "There are inaccessible floors in this map\n"
# define ORDER_OF_ELEMENTS "Error in map file, check that the map element \
	is last and there are no extra characters between elements\n"
# define MISSING_PATH "Texture path missing\n"
# define DUPLICATES "Make sure you have only and at least one \
	value for each element\n"
# define NO_PLAYER_POS "There is no player position in the map\n"
# define ELEMENT_MISSING "One or more definition of elements is missing\n"
# define NO_MAP "Map element is missing\n"
# define INV_COLOR_CODE "Please check color codes for F and C elements\nRGB \
	values should be between 0-255\n"
# define MLX_ERR "MLX error occured"
# define SP_CONTENT_ERR "Please format the sprite element content as follows, \
	SP path/to/texture XX.XX XX.XX\n"
# define DOUBLE_ERR "Please check that your doubles are formatted correctly\n"
# define SP_COORD_ERR "Sprite coordinates are out of bounds\n"
# define DR_PATH_ERR "Door path is missing\n"
# include "meta.h"

typedef enum e_err
{
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
	MLX_ERROR,
	SP_CONTENT,
	SP_DOUBLE_ERR,
	SP_COORD,
	DOOR_PATH,
	ERR_COUNT
}	t_err;

// error.c
int		pr_err(t_err type);

#endif
