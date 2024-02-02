
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_three.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:43:19 by yzaim         #+#    #+#                 */
/*   Updated: 2024/01/24 11:21:34 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	valid_sprite_content(char *content)
{
	uint32_t	content_count;
	uint16_t	i;

	i = 0;
	content_count = 0;
	while (content[i])
	{
		if (content[i] == ' ')
			content_count++;
		i++;
	}
	if (content[i] == '\0')
		content_count++;
	if (content_count == 3)
		return (true);
	return (false);
}

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

double	ft_atod(char *s)
{
	int		sign;
	double	decimal;
	int		x;
	double	num;

	num = 0.0;
	decimal = 0.0;
	sign = 1;
	x = 1;
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
	while (*s && ft_isdigit(*s))
	{
		decimal = decimal + (*s - '0') / (10 * x);
		s++;
		x++;
	}
	return ((num + decimal) * sign);
}