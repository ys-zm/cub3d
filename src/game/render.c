/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   render.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 23:14:20 by joppe         #+#    #+#                 */
/*   Updated: 2024/01/02 19:32:09 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


const t_rgba CELL_COLORS[] = {
	[MAP_EMPTY]	= {0xff00aaff},
	[MAP_WALL]	= {0x004ebaff},
	[MAP_SPACE]	= {0x696969ff},
};

void draw_cell(mlx_image_t *image, t_map *m, uint32_t cell_x, uint32_t cell_y)
{
	const size_t x_offset = (cell_x * CELL_WIDTH);
	const size_t y_offset = (cell_y * CELL_HEIGHT);

	const t_cell_type cell = (m->level[(cell_y * m->width) + cell_x]);

	draw_rect(image, x_offset, y_offset, CELL_WIDTH, CELL_HEIGHT, CELL_COLORS[cell].value);
}

void render_clear_bg(mlx_image_t *image)
{
	const uint32_t	size = image->width * image->height;
	size_t			i;

	i = 0;
	while (i < size)
	{
		mlx_put_pixel(image, i, 0, COLOR_BACKGROUND);
		i++;
	}
}


//////////////////////////
t_vec2d	calculate_draw_start_and_end1(double ray_length, uint32_t h)
{
	//calculate lowest and highest pixel to fill in current stripe
	uint32_t	start;
	uint32_t	end;
	double		line_height;

	line_height = (int)(h / ray_length);
	if (line_height > h)
		line_height = h;
	start = -line_height / 2 + ((double)h) / 2;
	end = line_height / 2 + ((double)h) / 2;
	if (end >= h)
		end = h - 1;
	return ((t_vec2d) {start, end});
}

void	draw_column1(t_meta *meta, t_vec2d line, t_side side, uint32_t col, uint32_t h)
{
	uint32_t    color;
	uint32_t    row;

	row = 0;
	// draw_col(meta->image, start, end, color);
	while (row < h)
	{
		// ceiling
		if (row < line.x)
		{
			color = set_color(0, 0, 0, 255);
		}
		// floor
		else if (row > line.y)
		{
			color = set_color(255, 255, 255, 255);
		}
		else
		{
			color = find_wall_color(side);
		} 
		mlx_put_pixel(meta->image, col, row, color);
		row++;
	}
}

void render_player_viewport(mlx_image_t *image, t_player *p)
{
	uint32_t i = 0;
	while(i < image->width)
	{
		t_vec2d line = calculate_draw_start_and_end1(p->rays[i].length, image->height);
		draw_column1(p->meta, line, p->rays[i].hit_side, i, image->height);
		i++;
	}
}

void render_minimap(mlx_image_t *image, t_map *m)
{
	size_t cell_y;
	size_t cell_x;

	cell_y = 0;
	while (cell_y < m->height)
	{
		cell_x = 0;
		while (cell_x < m->width)
		{
			draw_cell(image, m, cell_x, cell_y);
			cell_x++;
		}
		cell_y++;
	}
}

