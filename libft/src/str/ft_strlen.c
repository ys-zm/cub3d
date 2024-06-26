/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_strlen.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/03/05 17:04:36 by joppe         #+#    #+#                 */
/*   Updated: 2024/03/05 17:04:37 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}
