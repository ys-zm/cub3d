/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_free.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/18 21:56:37 by joppe         #+#    #+#                 */
/*   Updated: 2023/03/18 21:57:43 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*buf;
	size_t	total_size;

	total_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	buf = (char *) malloc(total_size);
	if (!buf)
		return (NULL);
	ft_strlcpy(buf, s1, ft_strlen(s1) + 1);
	ft_strlcat(buf, s2, total_size);
	free(s1);
	return (buf);
}
