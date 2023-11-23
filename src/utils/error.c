/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:08:19 by yzaim             #+#    #+#             */
/*   Updated: 2023/11/09 18:52:24 by yzaim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"

int	pr(char *err, int exit_code)
{
	write(2, err, ft_strlen(err));
	return (exit_code);
}

int pr_err(t_err type)
{
	char	*msg[11] = {INVALID_CHAR, INVALID_EXT, INVALID_WALLS,TOO_MANY_PLAYERS, INVALID_FILE, MALLOC_FAIL, WRO_ARGS, OOB_FLOOR, ORDER_OF_ELEMENTS, MISSING_PATH, DUPLICATES};

	if (type > 0 && type < 11)
		return (write(2, msg[type], ft_strlen(msg[type])), 1);
	return (0);
}