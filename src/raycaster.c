/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   raycaster.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/12/15 15:20:09 by jboeve        #+#    #+#                 */
/*   Updated: 2023/12/15 19:32:00 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "meta.h"
#include "vector.h"
#include <stdint.h>
#include <math.h>
#include <stdio.h>




t_ray raycaster_cast(t_meta *m, t_vec2f start, t_vec2f direction, t_ray_hit_check *hit)
{
	t_ray r;
	ft_bzero(&r, sizeof(t_ray));
	t_vec2f		delta_distance;
	t_vec2i		step;
	t_vec2i		map_pos;
	t_vec2f		side_distance;


	delta_distance[VEC_X] = (direction[VEC_X] == 0) ? 1e30 : fabs(1 / direction[VEC_X]);
	delta_distance[VEC_Y] = (direction[VEC_Y] == 0) ? 1e30 : fabs(1 / direction[VEC_Y]);

	t_vec2f p_pos = start;
	map_pos = vec2f_to_vec2i(p_pos);

	if (direction[VEC_X] < 0)
	{
		step[VEC_X] = -1;
		side_distance[VEC_X] = (p_pos[VEC_X] - map_pos[VEC_X]) * delta_distance[VEC_X];
	}
	else
	{
		step[VEC_X] = 1;
		side_distance[VEC_X] = (map_pos[VEC_X] + 1.0f - p_pos[VEC_X]) * delta_distance[VEC_X];
	}
	if (direction[VEC_Y] < 0)
	{
		step[VEC_Y] = -1;
		side_distance[VEC_Y] = (p_pos[VEC_Y] - map_pos[VEC_Y]) * delta_distance[VEC_Y];
	}
	else
	{
		step[VEC_Y] = 1;
		side_distance[VEC_Y] = (map_pos[VEC_Y] + 1.0f - p_pos[VEC_Y]) * delta_distance[VEC_Y];
	}

	r.hit = false;
	while (!r.hit)
	{
		if (side_distance[VEC_X] < side_distance[VEC_Y])	
		{
			side_distance[VEC_X] += delta_distance[VEC_X];
			map_pos[VEC_X] += step[VEC_X];
			r.hit_side = HIT_NS;
		}
		else
		{
			side_distance[VEC_Y] += delta_distance[VEC_Y];
			map_pos[VEC_Y] += step[VEC_Y];
			r.hit_side = HIT_EW;
		}
		r.hit = *hit;
	}

	if(r.hit_side == HIT_EW)
	{
		r.len = (side_distance[VEC_Y] - delta_distance[VEC_Y]);
	}
	else
		r.len = (side_distance[VEC_X] - delta_distance[VEC_X]);

	r.end = direction * (t_vec2f) {r.len, r.len} + vec2i_to_vec2f(map_pos);
	return r;
}
