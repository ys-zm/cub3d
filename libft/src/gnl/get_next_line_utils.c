/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 21:42:18 by joppe         #+#    #+#                 */
/*   Updated: 2023/03/08 09:24:56 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*s_sub;

	i = 0;
	if (!s)
		return (NULL);
	s_len = gnl_strlen((char *) s);
	if (start > s_len)
		return (gnl_strdup(""));
	s_len -= start;
	if (len > s_len)
		len = s_len;
	s_sub = malloc(sizeof(char) * (len + 1));
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

char	*gnl_strchr(const char *s, int c)
{
	int	i;
	int	len;

	len = gnl_strlen((char *) s) + 1;
	i = 0;
	while (i < len)
	{
		if (s[i] == (char) c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

int	gnl_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strdup(const char *s)
{
	int		i;
	int		len;
	char	*buffer;

	len = gnl_strlen((char *) s);
	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);
	i = 0;
	while (i < len)
	{
		buffer[i] = s[i];
		i++;
	}
	buffer[i] = 0;
	return (buffer);
}

char	*gnl_strjoin_free(char *s_base, char *s_append)
{
	int		i;
	int		len_base;
	int		len_append;
	char	*s_new;

	len_base = gnl_strlen(s_base);
	len_append = gnl_strlen(s_append);
	s_new = malloc(len_base + len_append + 1);
	if (!s_new)
		return (free(s_base), (NULL));
	i = 0;
	while (s_base[i])
	{
		s_new[i] = s_base[i];
		i++;
	}
	i = 0;
	while (s_append[i])
	{
		s_new[len_base + i] = s_append[i];
		i++;
	}
	free(s_base);
	s_new[len_base + len_append] = 0;
	return (s_new);
}
