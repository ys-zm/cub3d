/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   math_utils.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/12/14 18:30:23 by jboeve        #+#    #+#                 */
/*   Updated: 2023/12/14 18:44:48 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

t_vec2f	vec2f_abs(t_vec2f vec)
{
	return ((t_vec2f){fabs(vec[VEC_X]), fabs(vec[VEC_Y])});
}
