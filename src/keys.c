/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   keys.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 23:03:00 by joppe         #+#    #+#                 */
/*   Updated: 2023/11/10 16:56:16 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"

void keyhook(mlx_key_data_t keydata, void* param)
{
	t_meta *meta = param;

	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(meta->mlx);
}
