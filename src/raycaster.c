/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   raycaster.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/12/15 15:20:09 by jboeve        #+#    #+#                 */
/*   Updated: 2023/12/15 16:10:31 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "meta.h"
#include "vector.h"
#include <stdint.h>
#include <math.h>



t_ray raycaster_cast(t_vec2f start, t_vec2f direction, t_ray_hit_check *hit)
{
	t_ray r;
	ft_bzero(&r, sizeof(t_ray));


	r.delta_distance[VEC_X] = (direction[VEC_X] == 0) ? 1e30 : fabs(1 / direction[VEC_X]);
	r.delta_distance[VEC_Y] = (direction[VEC_Y] == 0) ? 1e30 : fabs(1 / direction[VEC_Y]);

	// t_vec2i p_pos = vec2f_to_vec2i(p.position) / (t_vec2i) {CELL_SIZE, CELL_SIZE};
	t_vec2f p_pos = start;
	r.map_pos = vec2f_to_vec2i(p_pos);

	if (direction[VEC_X] < 0)
	{
		r.step[VEC_X] = -1;
		r.side_distance[VEC_X] = (p_pos[VEC_X] - r.map_pos[VEC_X]) * r.delta_distance[VEC_X];
	}
	else
	{
		r.step[VEC_X] = 1;
		r.side_distance[VEC_X] = (r.map_pos[VEC_X] + 1.0f - p_pos[VEC_X]) * r.delta_distance[VEC_X];
	}
	if (direction[VEC_Y] < 0)
	{
		r.step[VEC_Y] = -1;
		r.side_distance[VEC_Y] = (p_pos[VEC_Y] - r.map_pos[VEC_Y]) * r.delta_distance[VEC_Y];
	}
	else
	{
		r.step[VEC_Y] = 1;
		r.side_distance[VEC_Y] = (r.map_pos[VEC_Y] + 1.0f - p_pos[VEC_Y]) * r.delta_distance[VEC_Y];
	}

	r.hit = false;
	while (!r.hit)
	{
		if (r.side_distance[VEC_X] < r.side_distance[VEC_Y])	
		{
			r.side_distance[VEC_X] += r.delta_distance[VEC_X];
			r.map_pos[VEC_X] += r.step[VEC_X];
			r.hit_side = HIT_NS;
		}
		else
		{
			r.side_distance[VEC_Y] += r.delta_distance[VEC_Y];
			r.map_pos[VEC_Y] += r.step[VEC_Y];
			r.hit_side = HIT_EW;
		}
		r.hit = *hit;
	}

	if(r.hit_side == HIT_EW)
	{
		r.perp_wall_distance = (r.side_distance[VEC_Y] - r.delta_distance[VEC_Y]);
	}
	else
		r.perp_wall_distance = (r.side_distance[VEC_X] - r.delta_distance[VEC_X]);


	// r.len = (int)(p.meta.image.height / r.perp_wall_distance);
	// TODO LEFT OFF HERE
	// printf("ray len %d\n", r.perp_wall_distance);

	return r;
}
