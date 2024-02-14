/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   double_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:30:18 by yzaim         #+#    #+#                 */
/*   Updated: 2024/02/14 17:45:45 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_double(char *s)
{
	if (!ft_isdigit(*s))
		return (pr_err(SP_DOUBLE_ERR), false);
	while (*s && ft_isdigit(*s))
		s++;
	if (*s != '.')
		return (pr_err(SP_DOUBLE_ERR), false);
	s++;
	while (*s && ft_isdigit(*s))
		s++;
	if (*s != '\0')
		return (pr_err(SP_DOUBLE_ERR), false);
	return (true);
}

double	calculate_decimal(char *s)
{
	double	decimal;
	int		x;

	x = 1;
	while (*s && ft_isdigit(*s))
	{
		decimal = decimal + (*s - '0') / (10 * x);
		s++;
		x++;
	}
	return (decimal);
}

double	ft_atod(char *s)
{
	int		sign;
	double	decimal;
	double	num;

	sign = 1;
	num = 0.0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if ((*s == '-' || *s == '+'))
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s && ft_isdigit(*s))
	{
		num = num * 10 + *s - '0';
		s++;
	}
	if (*s == '.')
		s++;
	decimal = calculate_decimal(s);
	return ((num + decimal) * sign);
}
