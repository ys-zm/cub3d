/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   render_minimap.h                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/03/01 19:29:27 by joppe         #+#    #+#                 */
/*   Updated: 2024/03/01 19:36:18 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_MINIMAP_H
#define RENDER_MINIMAP_H

#include "meta.h"

t_rgba	get_cell_color(t_cell_type cell);
void	render_clear_bg(mlx_image_t *image, uint32_t c);
t_cell_type	minimap_ray_len(const void *p, uint32_t x, uint32_t y);
void	draw_cell(mlx_image_t *image, t_cell_type cell, const uint32_t x, const uint32_t y);
void	render_border(mlx_image_t *image, uint32_t c);


#endif
