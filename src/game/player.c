/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                          :+:    :+:             */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:27:23 by yzaim         #+#    #+#                 */
/*   Updated: 2024/05/30 22:54:11 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "libft.h"
#include "meta.h"
#include "vector.h"
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

t_cell_type	bound_check(const void *param, uint32_t x, uint32_t y)
{
	t_meta *const	meta = (t_meta *) param;
	t_cell_type		cell;

	if (x < meta->map.width && y < meta->map.height)
	{
		cell = meta->map.level[(y * meta->map.width) + x];
		if (cell == MAP_WALL || cell == MAP_DOOR_CLOSED)
			return (cell);
	}
	return (MAP_EMPTY);
}

static t_cell_type	bound_check_interact(const void *p, uint32_t x, uint32_t y)
{
	t_meta *const	meta = (t_meta *) p;
	t_cell_type		cur_cell;

	if (x < meta->map.width && y < meta->map.height)
	{
		cur_cell = meta->map.level[(y * meta->map.width) + x];
		if (cur_cell == MAP_WALL || cur_cell == MAP_DOOR_CLOSED || cur_cell == MAP_DOOR_OPEN)
			return (cur_cell);
	}
	return (MAP_EMPTY);
}

static void	player_interactable_raycast(t_player *p)
{
	t_ray *const	r = &p->interact_ray;

	*r = raycaster_cast(p->position, p->direction, bound_check_interact, p->meta);
	if (world_is_interactable(r->hit_cell) && r->length < 1.5)
		;
	else
		ft_bzero(r, sizeof(t_ray));
}

void	player_interact(t_player *p)
{
	t_ray *const	r = &p->interact_ray;

	if (((char *) r)[0])
	{
		world_interact(p, r->end);
		player_raycast(p);
	}
}

void	player_raycast(t_player *p)
{
	const uint32_t	h = p->meta->image->height;
	uint32_t		i;
	t_vec2d			ray_start;
	double			camera_x;

	i = 0;
	player_interactable_raycast(p);
	while (i < h)
	{
		p->vrays[i] = floorcaster(p->position, p->direction, p->cam_plane, i);
		i++;
	}
	p->should_render = true;
	i = 0;
	while (i < p->meta->image->width)
	{
		camera_x = (2 * i / ((double) p->meta->image->width) - 1);
		ray_start = vec2d_add(p->direction, vec2d_scalar_product(p->cam_plane, camera_x));
		p->hrays[i] = raycaster_cast(p->position, ray_start, bound_check, p->meta);
		p->hrays[i].id = i;
		p->z_buffer[i] = p->hrays[i].length;
		i++;
	}
	sprite_calculate(p);
}
