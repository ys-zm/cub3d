/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 09:41:09 by joppe         #+#    #+#                 */
/*   Updated: 2022/11/01 17:56:01 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint8_t	ft_atou_8(const char *s)
{
	int	i;
	uint8_t	num;
	int	sign;

	num = 0;
	sign = 1;
	i = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	while ((s[i] == '-' || s[i] == '+'))
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] && ft_isdigit(s[i]))
	{
		num = num * 10 + s[i] - '0';
		i++;
	}
	return (num * sign);
}