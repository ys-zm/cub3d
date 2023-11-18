/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   draw.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/09 01:32:57 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/18 20:28:45 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "MLX42/MLX42.h"
#include "meta.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// TODO Struct that contains all this info because well. tHe nORm
void draw_rect(mlx_image_t* image, uint32_t x_pos, uint32_t y_pos, uint32_t width, uint32_t height, uint32_t color)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			draw_put_pixel(image, x_pos + x, y_pos + y, color);
			x++;
		}
		y++;
	}
}

void draw_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	if (x > 0 && x <= image->width && y > 0 && y <= image->height)
		mlx_put_pixel(image, x, y, color);
}
/////////////////////////////////////////////////

typedef struct s_bresenham
{
	t_vec2i 		current;
	t_vec2i 		end;
	t_vec2i 		delta;
	t_vec2i			direction;
	int32_t			slow_move;
}	t_bresenham;

static int32_t	direction(int32_t val)
{
	if (val)
		return (1);
	return (-1);
}

static void	bresenham_move(t_bresenham *line)
{
	if (line->delta[VEC_X] > line->delta[VEC_Y])
	{
		line->current[VEC_X] += line->direction[VEC_X];
		line->slow_move += line->delta[VEC_Y];
		if (line->slow_move * 2 >= line->delta[VEC_X])
		{
			line->current[VEC_Y] += line->direction[VEC_Y];
			line->slow_move -= line->delta[VEC_X];
		}
	}
	else
	{
		line->current[VEC_Y] += line->direction[VEC_Y];
		line->slow_move += line->delta[VEC_X];
		if (line->slow_move * 2 >= line->delta[VEC_Y])
		{
			line->current[VEC_X] += line->direction[VEC_X];
			line->slow_move -= line->delta[VEC_Y];
		}
	}
}

static void	bresenham(mlx_image_t *meta, t_bresenham *line, t_rgba c)
{
	if (line->delta[VEC_X] > line->delta[VEC_Y])
		line->slow_move = (line->delta[VEC_Y] - line->delta[VEC_X]) / 2;
	else
		line->slow_move = (line->delta[VEC_X] - line->delta[VEC_Y]) / 2;
	while (line->current[VEC_X] != line->end[VEC_X] || line->current[VEC_Y] != line->end[VEC_Y])
	{
		draw_put_pixel(meta, line->current[VEC_X], line->current[VEC_Y], c.value);
		bresenham_move(line);
	}
	draw_put_pixel(meta, line->current[VEC_X], line->current[VEC_Y], c.value);
}

void draw_line(mlx_image_t *image, t_vec2i start, t_vec2i end, t_rgba c)
{
	t_bresenham		line;

	line.current = start;
	line.end = end;

	line.delta[VEC_Y] = abs(line.current[VEC_Y] - line.end[VEC_Y]);
	line.delta[VEC_X] = abs(line.current[VEC_X] - line.end[VEC_X]);

	line.direction[VEC_Y] = direction(line.end[VEC_Y] - line.current[VEC_Y] > 0);
	line.direction[VEC_X] = direction(line.end[VEC_X] - line.current[VEC_X] > 0);
	bresenham(image, &line, c);
}

