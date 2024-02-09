/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_utils.c                                      :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:25:38 by yzaim         #+#    #+#                 */
/*   Updated: 2024/02/09 15:16:27 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include "test_utils.h"


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

void	print_double_array(char *msg, double *arr, uint32_t size, t_sprite *sp, int32_t *order)
{
	printf("%s: ", msg);
	for (int i = 0; i < size; i++)
	{
		printf("%lf", arr[i]);
		if (i < size - 1)
			printf(" | ");
	}
	printf("\n");
	printf("TEXTURES: ");
	for  (int i = 0; i < size; i++)
	{
		printf("%s", sp[order[i]].tex.tex_path + 17);
		if (i < size - 1)
			printf(" | ");
	}
	printf("\n");
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
	printf("\n");
}

void	print_sprites_array(t_sprite *arr, uint32_t size)
{
	uint32_t	i;

	i = 0;
	while (i < size)
	{
		printf("%d. SP %s %lf %lf\n", i, arr[i].tex.tex_path, arr[i].pos.x, arr[i].pos.y);
		i++;
	}
}

void	print_attributes(t_attr *attributes)
{
	printf("NO: %s\n", attributes->n.tex_path);
	printf("SO: %s\n", attributes->s.tex_path);
	printf("WE: %s\n", attributes->w.tex_path);
	printf("EA: %s\n", attributes->e.tex_path);
	if (attributes->f.tex_path)
		printf("F: %s\n", attributes->f.tex_path);
	else
		printf("F: %d,%d,%d\n", attributes->floor_c.r, attributes->floor_c.g, attributes->floor_c.b);
	if (attributes->c.tex_path)
		printf("C: %s\n", attributes->c.tex_path);
		else
		printf("C: %d,%d,%d\n", attributes->ceiling_c.r, attributes->ceiling_c.g, attributes->ceiling_c.b);
}

void	print_door_data(t_door doors)
{
	int	i = 0;
	printf("DOOR COUNT: %u\n", doors.door_count);
	printf("DOOR TEX: %s\n", doors.tex.tex_path);
	while (i < doors.door_count)
	{
		if (i == 0)
			printf("DOOR IDX: ");
		printf("%u", doors.idx[i]);
		if (i < doors.door_count - 1)
			printf(" | ");
		i++;
	}
	printf("\n");
}
