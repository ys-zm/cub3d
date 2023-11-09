/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 15:04:57 by joppe         #+#    #+#                 */
/*   Updated: 2022/11/03 10:39:02 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*s_ptr;
	char	*d_ptr;

	if (!dest && !src)
		return (dest);
	s_ptr = (char *) src;
	d_ptr = (char *) dest;
	i = 0;
	if (d_ptr > s_ptr)
		while (n--)
			d_ptr[n] = s_ptr[n];
	else
	{
		while (i < n)
		{
			d_ptr[i] = s_ptr[i];
			i++;
		}
	}
	return (dest);
}
