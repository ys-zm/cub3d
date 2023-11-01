/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   enemy.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/01 20:24:10 by jboeve        #+#    #+#                 */
/*   Updated: 2023/11/01 20:24:25 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"

t_enemy_obj *enemy_init(char *name)
{
	t_enemy_obj *e = calloc(sizeof(t_enemy), 1);

	return e;
}
