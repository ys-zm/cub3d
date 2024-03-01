/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   error.c                                           :+:    :+:             */
/*+:+ +:+ +:+ */
/*   By: yzaim <marvin@42.fr>   +#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2023/11/09 18:08:19 by yzaim #+##+# */
/*   Updated: 2024/02/28 14:17:02 by jboeve        ########   odam.nl         */
/**/
/* ************************************************************************** */

#include "meta.h"
#include "error.h"
#include <stdio.h>

int	pr(char *err, int exit_code)
{
	write(2, err, ft_strlen(err));
	return (exit_code);
}

int	pr_err(t_err type)
{
	const char	*msg[ERR_COUNT] = {
		INVALID_CHAR, INVALID_EXT, INVALID_WALLS,
		TOO_MANY_PLAYERS, INVALID_FILE,
		MALLOC_FAIL, WRO_ARGS, OOB_FLOOR,
		ORDER_OF_ELEMENTS, MISSING_PATH, DUPLICATES,
		NO_PLAYER_POS, ELEMENT_MISSING, NO_MAP,
		INV_COLOR_CODE, MLX_ERR, SP_CONTENT_ERR,
		DOUBLE_ERR, SP_COORD_ERR, DR_PATH_ERR
	};

	write(2, "Error\n", 6);
	if (type >= 0 && type < ERR_COUNT)
		return (write(2, msg[type], ft_strlen(msg[type])), 1);
	return (0);
}
