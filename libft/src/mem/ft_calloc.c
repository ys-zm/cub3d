/* ************************************************************************** */
/**/
/*   :::::::: */
/*   ft_calloc.c   :+::+: */
/*+:+ */
/*   By: joppe <jboeve@student.codam.nl> +#+  */
/*  +#+   */
/*   Created: 2023/11/10 00:29:23 by joppe #+##+# */
/*   Updated: 2023/11/10 00:29:23 by joppe ########   odam.nl */
/**/
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	buf_size;
	void	*buffer;

	buf_size = nmemb * size;
	buffer = malloc(buf_size);
	if (buffer)
		ft_bzero(buffer, buf_size);
	else
		return (NULL);
	return (buffer);
}
