/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 22:35:05 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/14 17:45:59 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"

int32_t set_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

int32_t find_wall_color(t_side side)
{
	int32_t color;

	if (side == HIT_NS)
		color = set_color(75, 0, 130, 255);
	else
		color = set_color(138, 48, 226, 255);
	return (color);
}