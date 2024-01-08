/* ************************************************************************** */
/**/
/*::::::::*/
/*   ft_strnstr.c   :+::+:*/
/* +:+*/
/*   By: jboeve <jboeve@student.codam.nl> +#+ */
/*   +#+  */
/*   Created: 2022/10/10 14:32:54 by jboeve#+##+# */
/*   Updated: 2022/11/03 14:07:24 by jboeve########   odam.nl */
/**/
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	len_needle;

	len_needle = ft_strlen(needle);
	if (!needle[0])
		return ((char *) haystack);
	i = 0;
	while (haystack[i] && i < n)
	{
		j = 0;
		while ((needle[j] == haystack[j + i] && i + j < n) || !needle[j])
		{
			if (!needle[j] && j == len_needle)
				return ((char *)(haystack + (i)));
			j++;
		}
		i++;
	}
	return (NULL);
}
