/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   test_utils.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/10 16:32:18 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/16 01:12:09 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "meta.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

const char *CELL_NAMES[] = {
	[MAP_EMPTY]	= "MAP_EMPTY",
	[MAP_WALL]	= "MAP_WALL",
	[MAP_SPACE]	= "MAP_SPACE",
};


void print_vec2f(const char *s, t_vec2f vec)
{
	printf("[%s] [%f][%f]\n",s, vec[VEC_X], vec[VEC_Y]);
}

void print_vec2i(const char *s, t_vec2i vec)
{
	printf("[%s] [%d][%d]\n",s, vec[VEC_X], vec[VEC_Y]);
}

void print_ray(const char *s, t_ray r)
{
	printf("[%s]\n", s);
	print_vec2f("ray_start", r.start);
	print_vec2f("ray_end", r.end);
	printf("ray_len [%f]\n", r.len);
}

void 	print_cell(t_cell_type cell)
{
	printf("cell [%s]\n", CELL_NAMES[cell]);
}

void print_map(char *map, uint32_t w, uint32_t h)
{
	size_t i = 0;
	while (map[i] && i < w * h)
	{
		printf("map [%.*s]\n", w, map + i);
		i += w;
	}

}

void print_map_cell(t_cell_type *level, uint32_t w, uint32_t h)
{
	size_t i = 0;
	size_t k = 0;
	size_t j;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			printf("%d", level[k]);
			k++;
			j++;
		}
		printf("\n");
		i++;
	}
}
