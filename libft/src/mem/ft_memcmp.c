/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboeve <jboeve@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:23:24 by jboeve        #+#    #+#                 */
/*   Updated: 2022/11/03 11:42:48 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_p;
	unsigned char	*s2_p;

	s1_p = (unsigned char *) s1;
	s2_p = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (s1_p[i] != s2_p[i])
			return (s1_p[i] - s2_p[i]);
		i++;
	}
	return (0);
}
