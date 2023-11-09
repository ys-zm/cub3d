/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jboeve <jboeve@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 11:38:15 by jboeve        #+#    #+#                 */
/*   Updated: 2022/11/03 14:51:31 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*s_sub;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	s_len -= start;
	if (len > s_len)
		len = s_len;
	s_sub = (char *) malloc(sizeof(char) * (len + 1));
	if (!s_sub)
		return (NULL);
	while (i < len)
	{
		s_sub[i] = s[start + i];
		i++;
	}
	s_sub[i] = 0;
	return (s_sub);
}
