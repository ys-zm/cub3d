/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ft_atoi_hex.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/19 23:37:48 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/19 23:45:46 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

uint32_t	ft_atoi_hex(const char *s)
{
	unsigned int	i;
	uint32_t		num;

	i = 0;
	num = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X'))
		i = 2;
	while (s[i])
	{
		if (s[i] >= 'a' && s[i] <= 'f')
			num = (num * 16) + (s[i] - 'a') + 10;
		else if (s[i] >= 'A' && s[i] <= 'F')
			num = (num * 16) + (s[i] - 'A') + 10;
		else if (s[i] >= '0' && s[i] <= '9')
			num = (num * 16) + s[i] - '0';
		else
			break ;
		i++;
	}
	return (num);
}
