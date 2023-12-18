/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   raycaster.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/12/15 15:20:09 by jboeve        #+#    #+#                 */
/*   Updated: 2023/12/15 15:33:21 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "meta.h"
#include "vector.h"
#include <stdint.h>
# include <math.h>

bool check_hit(t_meta *meta, uint32_t x, uint32_t y)
{
	if (meta->map.level[find_index(meta, x, y)] == MAP_WALL)
		return (true);
	return (false);
}

t_ray raycaster_cast(t_meta *meta, t_vec2f p_position, float angle, t_vec2f direction)
{
	t_ray r;
	ft_bzero(&r, sizeof(t_ray));
	(void)angle;
	(void)direction;
	
	r.delta_distance[VEC_X] = (r.direction[VEC_X] == 0) ? 1e30 : fabs(1 / r.direction[VEC_X]);
	r.delta_distance[VEC_Y] = (r.direction[VEC_Y] == 0) ? 1e30 : fabs(1 / r.direction[VEC_Y]);

	t_vec2i p_pos = vec2f_to_vec2i(p_position) / (t_vec2i) {CELL_SIZE, CELL_SIZE};
	r.map_pos = p_pos;

	if (r.direction[VEC_X] < 0)
	{
		r.step[VEC_X] = -1;
		r.side_distance[VEC_X] = (p_pos[VEC_X] - r.map_pos[VEC_X]) * r.delta_distance[VEC_X];
	}
	else
	{
		r.step[VEC_X] = 1;
		r.side_distance[VEC_X] = (r.map_pos[VEC_X] + 1.0f - p_pos[VEC_X]) * r.delta_distance[VEC_X];
	}
	if (r.direction[VEC_Y] < 0)
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
		r.hit = check_hit(meta, r.map_pos[VEC_X], r.map_pos[VEC_Y]);
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

	return (r);
}
