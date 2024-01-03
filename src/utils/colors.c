/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 22:35:05 by joppe         #+#    #+#                 */
/*   Updated: 2024/01/03 22:43:23 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include <stdio.h>

int32_t set_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

int32_t find_wall_color(t_side side)
{
	int32_t color;

	if (side == HIT_NS)
		color = VIEWPORT_COLOR_WALL_NS;
	else
		color = VIEWPORT_COLOR_WALL_EW;
	return (color);
}
