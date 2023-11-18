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

#ifndef PASER_H
#define PASER_H

# define TOO_MANY_PLAYERS "Map should not have more than one player position\n"
# define INVALID_CHAR "Map has invalid characters\n"
# define INVALID_WALLS "Map walls are not closed\n"
# define INVALID_EXT "Map extension should be .cub\n"
# define INVALID_FILE "Map file failed to open\n"
# define MALLOC_FAIL "Malloc error\n"
# define WRO_ARGS "Wrong number of arguments\n"
# define OOB_FLOOR "There are inaccessible floors in this map\n"
# define MISSING_ELEMENTS "The definition of some elements are missing\n\
There should be 6 (SO, NO, EA, WE, F, C)\n"
# define TOO_MANY_ELEMENTS "You have define too many elements\n\
There should be 6 (SO, NO, EA, WE, F, C)\n"
# define ORDER_OF_ELEMENTS "Map element should be last\n"

#include "meta.h"

typedef enum e_err {
    INV_CHAR, 
    INV_EXT, 
    INV_WALLS,
    PLAY_ERR,
    INV_FILE,
    MALL_ERR,
    ARG_ERR,
    OUT_OF_BOUNDS,
    M_ELEMENTS,
    T_ELEMENTS,
    FILE_ORDER,
}   t_err;

// error.c
int pr_err(t_err type);

// check_map.c
int valid_char(char c);
int check_pos(char c);
int check_chars(char *map);
int count_elements(char *file);


#endif