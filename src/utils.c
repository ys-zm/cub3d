/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   utils.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/10 16:32:18 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/10 17:05:45 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "meta.h"
#include <stdio.h>

void print_vec2f(const char *s, t_vec2f vec)
{
	printf("[%s] [%f][%f]\n",s, vec[VEC_X], vec[VEC_Y]);
}

void print_vec2i(const char *s, t_vec2i vec)
{
	printf("[%s] [%d][%d]\n",s, vec[VEC_X], vec[VEC_Y]);
}
