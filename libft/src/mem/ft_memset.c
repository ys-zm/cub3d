/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboeve <jboeve@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 09:14:46 by jboeve        #+#    #+#                 */
/*   Updated: 2022/10/20 10:19:11 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	while (i < n)
	{
		ptr = (char *) s;
		*(ptr + i) = c;
		i++;
	}
	return (s);
}
