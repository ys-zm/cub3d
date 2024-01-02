/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   vector.h                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/01/02 19:07:15 by joppe         #+#    #+#                 */
/*   Updated: 2024/01/02 21:26:35 by joppe         ########   odam.nl         */
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
t_vec2d		vec2d_rotate(t_vec2d old, double radiant);
t_vec2d		vec2d_add(t_vec2d v1, t_vec2d v2);
t_vec2d		vec2u_to_vec2d(t_vec2u v);
double		deg_to_rad(float deg);
t_vec2d	vec2d_mul(t_vec2d v1, t_vec2d v2);
t_vec2d	vec2d_normalize(t_vec2d vec);


#endif // !VECTOR_H
