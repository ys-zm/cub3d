/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   raycaster.h                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/03/01 12:58:39 by jboeve        #+#    #+#                 */
/*   Updated: 2024/03/03 19:50:21 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "vector.h"
# include <math.h>
# include <stdbool.h>
# include "meta.h"

t_vec2d	calculate_delta_dist(t_vec2d ray_direction);
t_vec2d	calculate_side_dist(t_vec2d ray_direction, \
t_vec2d	player_pos, t_vec2i map_pos, t_vec2d delta_dist);
t_vec2i	calculate_step_size(t_vec2d ray_direction);
double	calculate_ray_length(t_side hit_side, \
t_vec2d	side_dist, t_vec2d delta_dist);

#endif // !RAYCASTER_H
