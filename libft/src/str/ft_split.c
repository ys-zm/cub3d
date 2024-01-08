/* ************************************************************************** */
/**/
/*::::::::*/
/*   ft_split.c :+::+:*/
/* +:+*/
/*   By: jboeve <jboeve@student.codam.nl> +#+ */
/*   +#+  */
/*   Created: 2022/10/13 11:47:26 by jboeve#+##+# */
/*   Updated: 2022/11/03 16:16:17 by jboeve########   odam.nl */
/**/
/* ************************************************************************** */

#include "libft.h"

static	int	count_words(char const *s, char c)
{
	int	i;
	int	count;
	int	at_word;

	i = 0;
	count = 0;
	at_word = 0;
	while (s[i])
	{
		if (s[i] != c && !at_word)
		{
			at_word = 1;
			count++;
		}
		else if (s[i] == c)
			at_word = 0;
		i++;
	}
	return (count);
}

static	char	**free_all(char **s_split, int i)
{
	while (i--)
		free(s_split[i]);
	free(s_split);
	return (NULL);
}

static	int	offset_delim(const char *s, int c, int i)
{
	while (s[i] == c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	int		j;
	size_t	i;
	int		start;
	char	**s_split;

	word_count = count_words(s, c);
	s_split = (char **) ft_calloc(word_count + 1, sizeof(char **));
	if (!s_split)
		return (NULL);
	i = 0;
	j = 0;
	start = 0;
	while (word_count--)
	{
		i = offset_delim(s, c, i);
		start = i;
		while (s[i] != c && i < ft_strlen(s))
			i++;
		s_split[j] = ft_substr(s, start, i - start);
		if (!s_split[j])
			return (free_all(s_split, j));
		j++;
	}
	return (s_split);
}
