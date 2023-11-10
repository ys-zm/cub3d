/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   player.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/10 02:25:34 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/10 17:28:21 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "meta.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>


void player_move(t_player *p, t_vec2f transform)
{
	p->position += transform;
	player_look(p, 0.0);
}

// TODO Just do a matrix mutliplication with a rotation matrix.
void player_look(t_player *p, double angle)
{
	const uint32_t len = 50;

	p->angle += angle;
	if (p->angle > 2 * PI)
		p->angle -= 2 * PI;
	else if (p->angle < 0)
		p->angle += 2 * PI;

	p->direction = vec2f_rotate2d(p->angle);
	p->beam = p->position + p->direction * (t_vec2f) {len, len};

	// print_vec2f("direction", p->direction);
	// print_vec2f("beam", p->beam);
	// print_vec2f("pos", p->position);
	player_raycast(p, NULL);
}

t_vec2i	vec2i_rotate2d(float angle)
{
	return ((t_vec2i) {(cos(angle)) - (sin(angle)), (sin(angle)) + (cos(angle))});
}

// TODO Abstract out.
// calculates the length of the p->beam.
void player_raycast(t_player *p, t_cell_type *map)
{
	UNUSED(map);
	const uint32_t len = 50;

	t_ray *r = &p->ray;
	r->start = vec2f_to_vec2i(p->position);

	// Choppy bbby
	r->end = r->start + vec2f_to_vec2i(vec2f_rotate2d(p->angle + 0.3f) * (t_vec2f) {50, 50});
}
