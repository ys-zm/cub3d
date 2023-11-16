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

#include "meta.h"

typedef enum e_err {
    INV_CHAR, 
    INV_EXT, 
    INV_WALLS,
    PLAY_ERR,
    INV_FILE,
    MALL_ERR,
    ARG_ERR
}   t_err;

// error.c
int pr_err(t_err type);

// check_map.c
int valid_char(char c);
int check_pos(char c);
int check_chars(char *map);
int find_index(t_meta *meta, uint32_t y, uint32_t x);


#endif