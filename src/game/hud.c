/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   hud.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/02/17 00:36:22 by joppe         #+#    #+#                 */
/*   Updated: 2024/02/17 00:47:23 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"
#include "parser.h"
#include <stddef.h>
#include <stdio.h>

void hud_set_text(t_hud *hud)
{
	
}


void hud_render_text(t_text *t)
{
	if (!t->redraw)
		return;
	if (!t->img)
	{
		t->img = cube_put_string(t->img, t->s, cube_get_font_atlas(t->font));
	}
}

void hud_render(t_hud *hud)
{
	size_t i = 0;
	const size_t hud_items = sizeof(t_hud) / sizeof(t_text);
	while (i < hud_items)
	{
		hud_render_text(hud[i]);
	}
}
