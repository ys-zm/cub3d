/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/09 01:32:57 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/09 17:55:11 by yzaim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "meta.h"

// TODO Struct that contains all this info because well. tHe nORm
void draw_square(mlx_image_t* image, uint32_t x_pos, uint32_t y_pos, uint32_t width, uint32_t height, uint32_t color)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < width)
	{
		x = 0;
		while (x < height)
		{
			cube_put_pixel(image, x_pos + x, y_pos + y, color);
			x++;
		}
		y++;
	}
}

void cube_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	mlx_put_pixel(image, x, y, color);
}
