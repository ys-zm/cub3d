/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   test_utils.h                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/01/18 13:59:19 by jboeve        #+#    #+#                 */
/*   Updated: 2024/02/10 02:01:19 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */



#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "meta.h"

static const char *CELL_NAMES[] = {
	[MAP_EMPTY]	= "MAP_EMPTY",
	[MAP_WALL]	= "MAP_WALL",
	[MAP_SPACE]	= "MAP_SPACE",
	[MAP_DOOR_OPEN]	= "MAP_DOOR_OPEN",
	[MAP_DOOR_CLOSED]	= "MAP_DOOR_CLOSED",
};



// test_utils.c
void	print_cell(t_cell_type cell);
void	print_map(char *map, uint32_t w, uint32_t h);
void	print_map_cell(t_cell_type *level, uint32_t w, uint32_t h);
void	print_ray(const char *s, const t_ray *r);
void print_direction(t_side dir);
void print_hit_side(const char *s, t_side hit_side);
#endif // !TEST_UTILS_H
