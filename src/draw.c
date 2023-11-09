/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   draw.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/09 01:32:57 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/09 01:57:32 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "meta.h"
#include <stdio.h>

void cube_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	mlx_put_pixel(image, x, y, color);
}
