/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   test_utils.h                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/01/18 13:59:19 by jboeve        #+#    #+#                 */
/*   Updated: 2024/01/18 14:10:07 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */



#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "meta.h"


// test_utils.c
void	print_cell(t_cell_type cell);
void	print_map(char *map, uint32_t w, uint32_t h);
void	print_map_cell(t_cell_type *level, uint32_t w, uint32_t h);
void	print_ray(const char *s, const t_ray *r);
void print_direction(t_side dir);
#endif // !TEST_UTILS_H
