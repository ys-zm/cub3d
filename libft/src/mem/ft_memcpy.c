/* ************************************************************************** */
/**/
/*::::::::*/
/*   ft_memcpy.c:+::+:*/
/* +:+*/
/*   By: joppe <marvin@42.fr> +#+ */
/*   +#+  */
/*   Created: 2022/10/05 14:30:38 by joppe #+##+# */
/*   Updated: 2022/11/03 14:08:33 by jboeve########   odam.nl */
/**/
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s_ptr;
	unsigned char	*d_ptr;

	if (!n)
		return (dest);
	if (!src && !dest)
		return (NULL);
	s_ptr = (unsigned char *) src;
	d_ptr = (unsigned char *) dest;
	i = 0;
	while (i < n)
	{
		d_ptr[i] = s_ptr[i];
		i++;
	}
	return ((void *) d_ptr);
}
