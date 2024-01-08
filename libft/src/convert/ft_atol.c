/* ************************************************************************** */
/**/
/*::::::::*/
/*   ft_atol.c  :+::+:*/
/* +:+*/
/*   By: joppe <jboeve@student.codam.nl>  +#+ */
/*   +#+  */
/*   Created: 2023/03/07 22:22:08 by joppe #+##+# */
/*   Updated: 2023/03/07 22:27:27 by joppe ########   odam.nl */
/**/
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *s)
{
	int		i;
	int		sign;
	long	num;

	num = 0;
	sign = 0;
	i = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	while ((s[i] == '-' || s[i] == '+') && !sign)
	{
		if (s[i] == '-')
			sign = -1;
		if (s[i] == '+')
			sign = 1;
		i++;
	}
	if (!sign)
		sign = 1;
	while (s[i] && ft_isdigit(s[i]))
	{
		num = num * 10 + s[i] - '0';
		i++;
	}
	return (num * sign);
}
