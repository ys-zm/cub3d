/* ************************************************************************** */
/**/
/*::::::::*/
/*   ft_strchr.c:+::+:*/
/* +:+*/
/*   By: joppe <jboeve@student.codam.nl>  +#+ */
/*   +#+  */
/*   Created: 2022/10/10 10:24:25 by joppe #+##+# */
/*   Updated: 2022/11/03 14:09:05 by jboeve########   odam.nl */
/**/
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	len;

	len = ft_strlen(s) + 1;
	i = 0;
	while (i < len)
	{
		if (s[i] == (char) c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}
