/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboeve <jboeve@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:01:20 by jboeve        #+#    #+#                 */
/*   Updated: 2024/02/08 17:31:59 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "vector.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

void	swap_doubles(double *a, double *b)
{
	double	tmp = *a;

	*a = *b;
	*b = tmp;
}

void	swap_ints(int32_t *a, int32_t *b)
{
	int32_t	tmp = *a;

	*a = *b;
	*b = tmp;
}