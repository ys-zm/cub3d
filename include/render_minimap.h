/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   render_minimap.h                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/03/01 19:29:27 by joppe         #+#    #+#                 */
/*   Updated: 2024/03/04 17:53:57 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_MINIMAP_H
# define RENDER_MINIMAP_H

# include "meta.h"
# include <stdint.h>

typedef enum e_minimap_zoom
{
	ZOOM_IN,
	ZOOM_OUT,
}	t_minimap_zoom;

t_rgba		get_cell_color(t_cell_type cell);
void		render_clear_bg(mlx_image_t *image, uint32_t c);
t_cell_type	minimap_ray_len(const void *p, uint32_t x, uint32_t y);
void		render_border(mlx_image_t *image, uint32_t c);
void		draw_cell(mlx_image_t *image, t_cell_type cell, \
			t_vec2u start, uint32_t size);

void		minimap_init(t_minimap *map);
void		minimap_zoom(t_minimap *m, t_minimap_zoom dir);

#endif
