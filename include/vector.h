/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   vector.h                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/11 03:51:14 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/18 13:21:55 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
#define VECTOR_H

#include <inttypes.h>
#include <sys/cdefs.h>


#define VEC_X 0
#define VEC_Y 1

// Use the SIMD Vector instructions (very cool :D) 
// https://gcc.gnu.org/onlinedocs/gcc-8.3.0/gcc/Vector-Extensions.html#Vector-Extensions
typedef float		t_vec2f __attribute__ ((vector_size (sizeof(float) * 2)));
typedef int32_t		t_vec2i __attribute__ ((vector_size (sizeof(int32_t) * 2)));
typedef uint32_t	t_vec2u __attribute__ ((vector_size (sizeof(uint32_t) * 2)));


// vector.c
t_vec2i	vec2f_to_vec2i(t_vec2f vec);
t_vec2f	vec2i_to_vec2f(t_vec2i vec);
t_vec2f	vec2f_rotate2d(float angle);
t_vec2f	vec2f_normalize(t_vec2f vec);
float	deg_to_rad(float deg);

#endif
