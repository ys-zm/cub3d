/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   game.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/08 22:35:05 by joppe         #+#    #+#                 */
/*   Updated: 2023/12/14 17:45:59 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "meta.h"
#include "timer.h"
#include "vector.h"
// #include <GLFW/glfw3.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

void print_vector(char *str, t_vector vector)
{
  printf("%s X: %f | Y: %f\n", str, vector.x, vector.y);
}

void game_init(t_meta *meta)
{
	t_player* const p = &meta->player;

	timer_init(&meta->update_timer, mlx_get_time);
	timer_start(&meta->update_timer);

	// setup player stuff.
	p->meta = meta;
	p->position.x = meta->map.player_start_x;
	p->position.y = meta->map.player_start_y;
  print_vector("CamPlane:", meta->player.cam_plane);
  print_vector("PLayerDir:", meta->player.direction);

}

int32_t set_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

int32_t find_wall_color(t_side side)
{
	int32_t color;

	if (side == HIT_NS)
		color = set_color(75, 0, 130, 255);
	else
		color = set_color(138, 48, 226, 255);
	return (color);
}


void calculate_delta_dist(t_meta *meta)
{
  t_ray_data *data = &meta->data;

  if (data->ray_direction.x == 0)
  {
    data->delta_distance.x = INT32_MAX;
  }
  else
  {
    data->delta_distance.x = fabs(1 / data->ray_direction.x);
  }
  if (data->ray_direction.y == 0)
  {
    data->delta_distance.y = INT32_MAX;
  }
  else
  {
    data->delta_distance.y = fabs(1 / data->ray_direction.y);
  }
}

void calculate_side_distance(t_meta *meta)
{
  t_ray_data *data = &meta->data;

  if (data->ray_direction.x < 0)
  {
    data->step.x = -1;
    data->side_distance.x = (meta->player.position.x - data->map_pos.x) * data->delta_distance.x;
  }
  else
  {
    data->step.x = 1;
    data->side_distance.x = (data->map_pos.x + 1.0 - meta->player.position.x) * data->delta_distance.x;
  }
  if (data->ray_direction.y < 0)
  {
    data->step.y = -1;
    data->side_distance.y = (meta->player.position.y - data->map_pos.y) * data->delta_distance.y;
  }
  else
  {
    data->step.y = 1;
    data->side_distance.y = (data->map_pos.y + 1.0 - meta->player.position.y) * data->delta_distance.y;
  }
}

void dda_algorithm(t_meta *meta)
{
  t_ray_data *data = &meta->data;
  data->hit = false;

  while (data->hit == false)
  {
    //jump to next map square, either in x-direction, or in y-direction
    if (data->side_distance.x < data->side_distance.y)
    {
      data->side_distance.x += data->delta_distance.x;
      data->map_pos.x += data->step.x;
      data->side = HIT_NS;
    }
    else
    {
      data->side_distance.y += data->delta_distance.y;
      data->map_pos.y += data->step.y;
      data->side = HIT_EW;
    }
    //Check if ray has hit a wall
    if (meta->map.level[find_index(meta, data->map_pos.x, data->map_pos.y)] == MAP_WALL)
    {
      data->hit = true;
    }
  }
}

void calculate_line_height(t_meta *meta, int h)
{
  t_ray_data *data = &meta->data;
	
  //Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
  if(data->side == HIT_NS)
  {
    data->perp_wall_distance = (data->side_distance.x - data->delta_distance.x);
  }
  else
  {
    data->perp_wall_distance = (data->side_distance.y - data->delta_distance.y);
  }
  
  //Calculate height of line to draw on screen
  data->line_height = (int) h / data->perp_wall_distance;
}

void calculate_draw_start_and_end(t_meta *meta, int h)
{
    //calculate lowest and highest pixel to fill in current stripe
    t_ray_data *data = &meta->data;

    data->start = -data->line_height / 2 + h / 2;
    if (data->start < 0)
      data->start = 0;
    data->end = data->line_height / 2 + h / 2;
    if ((int)data->end >= h)
      data->end = h - 1;
}

void draw_column(t_meta *meta, int col, int h)
{
  uint32_t color;
  int row;
  
  row = 0;
	// draw_col(meta->image, start, end, color);
	while (row <= (int)h)
	{
    // ceiling
		if (row < (int)meta->data.start)
		{
			color = set_color(0, 0, 0, 255);
		}
    // floor
		else if (row > (int)meta->data.end)
		{
			color = set_color(255, 255, 255, 255);
		}
		else
		{
			color = find_wall_color(meta->data.side);
		}
		mlx_put_pixel(meta->image, col, row, color);
		row++;
	}
}

void raycast_and_render(t_meta *meta)
{
	// create temps based on the lodev algo
	meta->data.plane.x = meta->player.cam_plane.x;
	meta->data.plane.y = meta->player.cam_plane.y;
	
	int w = meta->image->width;
	int h = meta->image->height;
  int col;
  col = 0;
	while(col < w)
  {
      //calculate ray position and direction
      meta->data.camera_x = 2 * col / (double)w; //x-coordinate in camera space
      meta->data.ray_direction.x = meta->player.direction.x + meta->data.plane.x * meta->data.camera_x;
      meta->data.ray_direction.y = meta->player.direction.y + meta->data.plane.y * meta->data.camera_x;
      meta->data.map_pos.x = (int)meta->player.position.x;
      meta->data.map_pos.y = (int)meta->player.position.y;
      calculate_delta_dist(meta);
      calculate_side_distance(meta);
      dda_algorithm(meta);
      print_vector("SideDist:", meta->data.side_distance);
      print_vector("DeltaDist:", meta->data.delta_distance);
      calculate_line_height(meta, h);
      calculate_draw_start_and_end(meta, h);
      draw_column(meta, col, h);
      col++;
  }
}



void game_loop(void* param)
{
	t_meta *const meta = param;

	raycast_and_render(meta);
}
