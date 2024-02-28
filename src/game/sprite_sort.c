/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboeve <jboeve@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:01:20 by jboeve        #+#    #+#                 */
/*   Updated: 2024/02/08 17:31:59 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "vector.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// TODO: find a better way to compare doubles
uint32_t	partition(double *sprite_dist, int32_t *sprite_order, \
					int32_t low, int32_t high)
{
	const double	pivot = sprite_dist[low];
	int32_t			i;
	int32_t			j;

	i = low;
	j = high;
	while (i < j)
	{
		while (sprite_dist[i] <= pivot && i <= high - 1)
			i++;
		while (sprite_dist[j] > pivot && j >= low + 1)
			j--;
		if (i < j)
		{
			swap_doubles(&sprite_dist[i], &sprite_dist[j]);
			swap_ints(&sprite_order[i], &sprite_order[j]);
		}
	}
	swap_doubles(&sprite_dist[low], &sprite_dist[j]);
	swap_ints(&sprite_order[low], &sprite_order[j]);
	return (j);
}

void	quick_sort(double *sprite_dist, int32_t *sprite_order, \
					int32_t low, int32_t high)
{
	int32_t	partition_index;

	if (low < high)
	{
		partition_index = partition(sprite_dist, sprite_order, low, high);
		quick_sort(sprite_dist, sprite_order, low, partition_index - 1);
		quick_sort(sprite_dist, sprite_order, partition_index + 1, high);
	}
}

void	reverse(double *arr1, int32_t *arr2, uint32_t size)
{
	uint32_t	i;
	double		tmp1;
	int32_t		tmp2;

	i = 0;
	while (i < size / 2)
	{
		tmp1 = arr1[i];
		arr1[i] = arr1[size - i - 1];
		arr1[size - i - 1] = tmp1;
		tmp2 = arr2[i];
		arr2[i] = arr2[size - i - 1];
		arr2[size - i - 1] = tmp2;
		i++;
	}
}

void	sprite_sort(double *sprite_dist, int32_t *sprite_order, \
					uint32_t sprite_count)
{
	quick_sort(sprite_dist, sprite_order, 0, sprite_count - 1);
	reverse(sprite_dist, sprite_order, sprite_count);
}
