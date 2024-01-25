/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   sprite_utils.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/01/25 16:01:20 by jboeve        #+#    #+#                 */
/*   Updated: 2024/01/25 16:58:20 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "vector.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

void	swap_doubles(double *a, double *b)
{
	double	tmp = *a;

	*a = *b;
	*b = tmp;
}

void	swap_ints(int32_t *a, int32_t *b)
{
	int32_t	tmp = *a;

	*a = *b;
	*b = tmp;
}

uint32_t	partition(double *sprite_dist, int32_t *sprite_order, uint32_t low, uint32_t high)
{
	double		pivot = sprite_dist[low];
	uint32_t	i = low;
	uint32_t	j = high;

	while (i < j)
	{
		// TODO: find a better way to compare doubles
		while (sprite_dist[i] <= pivot && i <= high - 1)
			i++;
		while (sprite_dist[j] > pivot && j >= low + 1)
			j--;
		if (i < j)
			swap_doubles(&sprite_dist[i], &sprite_dist[j]);
			swap_ints(&sprite_order[i], &sprite_order[j]);
	}
	swap_doubles(&sprite_dist[low], &sprite_dist[j]);
	swap_ints(&sprite_order[low], &sprite_order[i]);
	return (j);
}

void	quick_sort(double *sprite_dist, int32_t *sprite_order, uint32_t low, uint32_t high)
{
	if (low < high)
	{
		uint32_t	pivot = partition(sprite_dist, sprite_order, low, high);
		quick_sort(sprite_dist, sprite_order, low, pivot - 1);
		quick_sort(sprite_dist, sprite_order, pivot + 1, high);
	}
}

void	sprite_sort(double *sprite_dist, int32_t *sprite_order)
{
	print_double_array("SPRITE_DIST", sprite_dist, SPRITE_COUNT);
	print_ints_array("SPRITE_ORDER", sprite_order, SPRITE_COUNT);
	quick_sort(sprite_dist, sprite_order, 0, SPRITE_COUNT - 1);
	print_double_array("SPRITE_DIST", sprite_dist, SPRITE_COUNT);
	print_ints_array("SPRITE_ORDER", sprite_order, SPRITE_COUNT);
}