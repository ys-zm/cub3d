/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 09:46:55 by joppe         #+#    #+#                 */
/*   Updated: 2022/10/20 10:27:06 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*s_mapi;

	if (!s || !f)
		return (NULL);
	s_mapi = (char *) malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!s_mapi)
		return (NULL);
	i = 0;
	while (s[i])
	{
		s_mapi[i] = f((unsigned int) i, s[i]);
		i++;
	}
	s_mapi[i] = 0;
	return (s_mapi);
}
