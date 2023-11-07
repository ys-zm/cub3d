/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 20:12:33 by joppe         #+#    #+#                 */
/*   Updated: 2022/11/03 15:54:07 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	find_start(char const *s, char const *set)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_strchr(set, s[i]))
			break ;
		i++;
	}
	return (i);
}

static	int	find_end(char const *s, char const *set)
{
	int	i;

	i = ft_strlen(s);
	while (i)
	{
		if (!ft_strchr(set, s[i]))
			break ;
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	start = find_start(s1, set);
	end = find_end(s1, set);
	return (ft_substr(s1, start, end - start + 1));
}
