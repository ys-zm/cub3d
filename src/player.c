/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   player.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/10 02:25:34 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/10 03:25:24 by joppe         ########   odam.nl         */
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
	// TODO Find better way to update the player's "beam".
	player_look(p, 0.0);
}

// TODO Just do a matrix mutliplication with a rotation matrix.
void player_look(t_player *p, double angle)
{
	uint32_t len = 50;
	p->angle += angle;
	if (p->angle > 2 * PI)
		p->angle -= 2 * PI;
	else if (p->angle < 0)
		p->angle += 2 * PI;


	p->direction[VEC_X] = p->position[VEC_X] + cos(p->angle) * len;
	p->direction[VEC_Y] = p->position[VEC_Y] + sin(p->angle) * len;
	// printf("angle [%f]\n", p->angle);
}
