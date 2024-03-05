/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_strcmp_largest.c                               :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/03/04 11:42:00 by jboeve        #+#    #+#                 */
/*   Updated: 2024/03/05 17:07:56 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static size_t	strlen_largest(const char *s1, const char *s2)
{
	const size_t	l1 = ft_strlen(s1);
	const size_t	l2 = ft_strlen(s2);

	if (l1 > l2)
		return (l1);
	return (l2);
}

int	ft_strcmp_largest(const char *s1, const char *s2)
{
	size_t			i;
	const size_t	n = strlen_largest(s1, s2);

	i = 0;
	while (i < n && s1[i] && (s1[i] == s2[i]))
		i++;
	if (i == n)
		return (0);
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
