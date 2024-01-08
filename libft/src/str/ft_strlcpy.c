/* ************************************************************************** */
/**/
/*::::::::*/
/*   ft_strlcpy.c   :+::+:*/
/* +:+*/
/*   By: joppe <jboeve@student.codam.nl>  +#+ */
/*   +#+  */
/*   Created: 2022/10/06 09:27:16 by joppe #+##+# */
/*   Updated: 2022/10/29 21:56:02 by joppe ########   odam.nl */
/**/
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!size)
		return (ft_strlen(src));
	while (i < size - 1 && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (ft_strlen(src));
}
