/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   test_utils.h                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/01/02 19:56:05 by joppe         #+#    #+#                 */
/*   Updated: 2024/01/02 23:20:17 by joppe         ########   odam.nl         */
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

#endif // !TEST_UTILS_H
