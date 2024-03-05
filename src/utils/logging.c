/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   error.c                                           :+:    :+:             */
/*+:+ +:+ +:+ */
/*   By: yzaim <marvin@42.fr>   +#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2023/11/09 18:08:19 by yzaim #+##+# */
/*   Updated: 2024/03/03 19:18:09 by joppe         ########   odam.nl         */
/**/
/* ************************************************************************** */

#include "meta.h"
#include "logging.h"
#include <stdio.h>

int	pr(char *err, int exit_code)
{
	size_t	i;

	i = write(2, err, ft_strlen(err));
	(void) i;
	return (exit_code);
}

int	pr_err(t_err type)
{
	size_t		i;
	const char	*msg[ERR_COUNT] = {
		INVALID_CHAR, INVALID_EXT, INVALID_WALLS,
		TOO_MANY_PLAYERS, INVALID_FILE,
		MALLOC_FAIL, WRO_ARGS, OOB_FLOOR,
		ORDER_OF_ELEMENTS, MISSING_PATH, DUPLICATES,
		NO_PLAYER_POS, ELEMENT_MISSING, NO_MAP,
		INV_COLOR_CODE, MLX_ERR, SP_CONTENT_ERR,
		DOUBLE_ERR, SP_COORD_ERR, DR_PATH_ERR
	};

	i = write(2, "Error\n", 6);
	(void) i;
	if (type >= 0 && type < ERR_COUNT)
	{
		i = write(2, msg[type], ft_strlen(msg[type]));
		return (1);
	}
	return (0);
}
