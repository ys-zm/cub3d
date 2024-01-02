/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   vector.h                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/01/02 19:07:15 by joppe         #+#    #+#                 */
/*   Updated: 2024/01/03 00:26:44 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>


typedef struct s_vec2d {
	double	x;
	double	y;
}	t_vec2d;

typedef struct s_vec2i {
	int32_t	x;
	int32_t	y;
}	t_vec2i;

typedef struct s_vec2u {
	uint32_t	x;
	uint32_t	y;
}	t_vec2u;


// vec2d_utils.c
void		print_vec2d(char *str, t_vec2d vector);
t_vec2d		vec2d_scalar_product(t_vec2d vec, double scalar);
t_vec2i		vec2i_scalar_product(t_vec2i vec, double scalar);
t_vec2d		vec2d_rotate(t_vec2d old, double radiant);
t_vec2d		vec2d_add(t_vec2d v1, t_vec2d v2);
t_vec2d		vec2u_to_vec2d(t_vec2u v);
double		deg_to_rad(float deg);
t_vec2d	vec2d_mul(t_vec2d v1, t_vec2d v2);
t_vec2d	vec2d_normalize(t_vec2d vec);
t_vec2i vec2d_to_vec2i(t_vec2d v);
void print_vec2i(char *str, t_vec2i vector);


#endif // !VECTOR_H
