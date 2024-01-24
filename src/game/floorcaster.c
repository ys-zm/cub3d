/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floorcaster.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 13:13:37 by yzaim         #+#    #+#                 */
/*   Updated: 2024/01/24 16:06:35 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "meta.h"

t_vray floorcaster(t_vec2d pp, t_vec2d dir, t_vec2d cam_plane, uint32_t y)
{
	
	t_vray	ray;
	t_vec2d	raydir_left;
	t_vec2d	raydir_right;

	raydir_left = (t_vec2d){dir.x - cam_plane.x, dir.y - cam_plane.y};
	raydir_right = (t_vec2d){dir.x + cam_plane.x, dir.y + cam_plane.y};

	
	int	p = y - WINDOW_HEIGHT / 2;
	double	posZ = 0.5 * WINDOW_HEIGHT;
	double	row_distance = posZ / p;
	ray.step.x = row_distance * (raydir_right.x - raydir_left.x) / WINDOW_WIDTH;
	ray.step.y = row_distance * (raydir_right.y - raydir_left.y) / WINDOW_WIDTH;
	
	ray.floor.x = pp.x + row_distance + raydir_left.x;
	ray.floor.y = pp.y + row_distance + raydir_left.y;



	return (ray);
}