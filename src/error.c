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

// int pr_err(t_err type)
// {
// 	if (type == INV_CHAR)
// 		write(2, INVALID_CHAR, ft_strlen(INVALID_CHAR));
// 	if (type == INV_EXT)
// 		write(2, INVALID_EXT, ft_strlen(INVALID_EXT));
// 	if (type == INV_WALLS)
// 		write(2, INVALID_WALLS, ft_strlen(INVALID_WALLS));
// 	if (type == PLAY_ERR)
// 		write(2, TOO_MANY_PLAYERS, ft_strlen(TOO_MANY_PLAYERS));
// 	if (type == INV_FILE)
// 		write(2, INVALID_FILE, ft_strlen(INVALID_FILE));
// 	if (type == MALL_ERR)
// 		write(2, MALLOC_FAIL, ft_strlen(MALLOC_FAIL));
// 	if (type == ARG_ERR)
// 		write(2, WRO_ARGS, ft_strlen(WRO_ARGS));
// 	return (1);
// }

int pr_err(t_err type)
{
	t_err	errs[7] = {INV_CHAR, INV_EXT, INV_WALLS, PLAY_ERR, INV_FILE, MALL_ERR, ARG_ERR};
	char	*msg[7] = {INVALID_CHAR, INVALID_EXT, INVALID_WALLS, TOO_MANY_PLAYERS, INVALID_FILE, MALLOC_FAIL, WRO_ARGS};
	int		i;

	i = 0;
	while (errs[i] != type)
		i++;
	if (i < 7)
		return (write(2, msg[i], ft_strlen(msg[i])), 1);
	return (0);
}