/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   bresenham.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/03/01 19:07:26 by joppe         #+#    #+#                 */
/*   Updated: 2024/03/01 19:07:44 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "draw.h"

static int32_t	direction(int32_t val)
{
	if (val)
		return (1);
	return (-1);
}

static void	bresenham_move(t_bresenham *line)
{
	if (line->delta.x > line->delta.y)
	{
		line->current.x += line->direction.x;
		line->slow_move += line->delta.y;
		if (line->slow_move * 2 >= line->delta.x)
		{
			line->current.y += line->direction.y;
			line->slow_move -= line->delta.x;
		}
	}
	else
	{
		line->current.y += line->direction.y;
		line->slow_move += line->delta.x;
		if (line->slow_move * 2 >= line->delta.y)
		{
			line->current.x += line->direction.x;
			line->slow_move -= line->delta.y;
		}
	}
}

static void	bresenham(mlx_image_t *meta, t_bresenham *line, t_rgba c)
{
	if (line->delta.x > line->delta.y)
		line->slow_move = (line->delta.y - line->delta.x) / 2;
	else
		line->slow_move = (line->delta.x - line->delta.y) / 2;
	while (line->current.x != line->end.x || line->current.y != line->end.y)
	{
		draw_put_pixel(meta, line->current.x, line->current.y, c.value);
		bresenham_move(line);
	}
	draw_put_pixel(meta, line->current.x, line->current.y, c.value);
}

void	draw_line(mlx_image_t *image, t_vec2i start, t_vec2i end, t_rgba c)
{
	t_bresenham		line;

	line.current = start;
	line.end = end;
	line.delta.y = abs(line.current.y - line.end.y);
	line.delta.x = abs(line.current.x - line.end.x);
	line.direction.y = direction(line.end.y - line.current.y > 0);
	line.direction.x = direction(line.end.x - line.current.x > 0);
	bresenham(image, &line, c);
}
