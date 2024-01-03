/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   vec_utils.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/01/03 17:54:28 by joppe         #+#    #+#                 */
/*   Updated: 2024/01/03 17:55:45 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <stdio.h>

void print_vec2d(char *str, t_vec2d vector)
{
 	printf("%s [%lf][%lf]\n", str, vector.x, vector.y);
}

void print_vec2i(char *str, t_vec2i vector)
{
 	printf("%s [%d][%d]\n", str, vector.x, vector.y);
}

t_vec2d	vec2i_to_vec2d(t_vec2i v)
{
	return (t_vec2d) {v.x, v.y};
}

t_vec2d vec2u_to_vec2d(t_vec2u v)
{
	return (t_vec2d) {v.x, v.y};
}

t_vec2i vec2d_to_vec2i(t_vec2d v)
{
	return (t_vec2i) {v.x, v.y};
}


