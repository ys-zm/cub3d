/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 00:22:38 by joppe         #+#    #+#                 */
/*   Updated: 2022/11/03 15:53:44 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	int_len(int n)
{
	int	i;

	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	int		sign;
	int		value;
	char	*s;

	if (!n)
		return (ft_strdup("0"));
	sign = (n < 0);
	i = int_len(n) + sign;
	s = ft_calloc(sizeof(char), i + 1);
	if (!s)
		return (NULL);
	if (sign)
		s[0] = '-';
	s[i--] = 0;
	while (n)
	{
		value = (n % 10);
		if (sign)
			value *= -1;
		s[i--] = value + '0';
		n /= 10;
	}
	return (s);
}
