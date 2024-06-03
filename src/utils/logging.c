/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   logging.c                                         :+:    :+:             */
/*+:+ +:+ +:+ */
/*   By: yzaim <marvin@42.fr>   +#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2023/11/09 18:08:19 by yzaim #+##+# */
/*   Updated: 2024/05/30 16:26:50 by yesimzaim     ########   odam.nl         */
/**/
/* ************************************************************************** */

#include "meta.h"
#include "logging.h"
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
		DOUBLE_ERR, SP_COORD_ERR, DR_PATH_ERR, DR_ERR
	};

	write(2, "Error\n", 6);
	if (type >= 0 && type < ERR_COUNT)
	{
		write(2, msg[type], ft_strlen(msg[type]));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
