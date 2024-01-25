/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                      :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:25:38 by yzaim             #+#    #+#             */
/*   Updated: 2024/01/18 14:10:17 by jboeve        ########   odam.nl         */
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

void print_ray(const char *s, const t_ray *r)
{
	char *side_text;
	if (r->hit_side == SIDE_S || r->hit_side == SIDE_N)
		side_text = "NS";
	else
		side_text = "EW";
	printf("[%s] | ray_direction [%lf][%lf] | length [%lf] | ray_end [%lf][%lf] | hit_side [%s]\n", s, r->direction.x, r->direction.y, r->length, r->end.x, r->end.y, side_text);
}

void print_direction(t_side dir)
{
	const char *text[4] = {
		[SIDE_N] = "N",
		[SIDE_E] = "E",
		[SIDE_S] = "S",
		[SIDE_W] = "W",
	};

	printf("[%s]\n", text[dir]);
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

void	print_double_array(char *msg, double *arr, uint32_t size)
{
	printf("%s :", msg);
	for (int i = 0; i < size; i++)
	{
		printf("%lf", arr[i]);
		if (i < size - 1)
			printf(" | ");
	}
}

void	print_ints_array(char *msg, int32_t *arr, uint32_t size)
{
	printf("%s :", msg);
	for (int i = 0; i < size; i++)
	{
		printf("%u", arr[i]);
		if (i < size - 1)
			printf(" | ");
	}
}