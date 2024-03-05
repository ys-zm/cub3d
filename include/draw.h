/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   draw.h                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/03/01 18:06:27 by joppe         #+#    #+#                 */
/*   Updated: 2024/03/03 19:52:04 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "vector.h"

typedef struct s_bresenham
{
	t_vec2i			current;
	t_vec2i			end;
	t_vec2i			delta;
	t_vec2i			direction;
	int32_t			slow_move;
}	t_bresenham;

#endif
