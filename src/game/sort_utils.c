/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_utils.c                                      :+:    :+:             */
/*                                                     +:+                    */
/*   By: jboeve <jboeve@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:01:20 by jboeve        #+#    #+#                 */
/*   Updated: 2024/02/29 15:55:45 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

void	swap_doubles(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	swap_ints(int32_t *a, int32_t *b)
{
	int32_t	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
