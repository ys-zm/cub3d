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
}
