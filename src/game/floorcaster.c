/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floorcaster.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:13:37 by yzaim         #+#    #+#                 */
/*   Updated: 2024/01/24 13:29:23 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"

t_vec2d	floorcaster(t_vec2d pp, t_vec2d dir, t_vec2d cam_plane, uint32_t y)
{
	t_vec2d	raydir_left;
	t_vec2d	raydir_right;

	raydir_left = (t_vec2d){dir.x - cam_plane.x, dir.y - cam_plane.y};
	raydir_right = (t_vec2d){dir.x + cam_plane.x, dir.y + cam_plane.y};
	
	int	p = y - WINDOW_HEIGHT / 2;
	double	posZ = 0.5 * WINDOW_HEIGHT;
	double	row_distance = posZ / p;
	t_vec2d	floor_step;
	floor_step.x = row_distance * (raydir_right.x - raydir_left.x) / WINDOW_WIDTH;
	floor_step.y = row_distance * (raydir_right.y - raydir_left.y) / WINDOW_WIDTH;
	
	t_vec2d	floor;
	floor.x = pp.x + row_distance + raydir_left.x;
	floor.y = pp.y + row_distance + raydir_left.y;
	return (floor);
}