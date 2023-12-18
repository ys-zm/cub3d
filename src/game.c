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

void game_init(t_meta *meta)
{
	t_player* const p = &meta->player;

	timer_init(&meta->update_timer, mlx_get_time);
	timer_start(&meta->update_timer);

	// setup player stuff.
	p->meta = meta;
	p->position.x = meta->map.player_start_x;
	p->position.y = meta->map.player_start_y;

}

int32_t set_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

int32_t find_wall_color(t_side side)
{
	int32_t color;

	if (side == HIT_NS)
		color = set_color(0, 240, 60, 255);
	else
		color = set_color(0, 230, 20, 255);
	return (color);
}


void raycast_and_render(t_meta *meta)
{
	// create temps based on the lodev algo
	meta->data.plane.x = 0;
	meta->data.plane.y = 0.66;
	double posX = meta->player.position.x, posY = meta->player.position.y;  //x and y start position
	float dirX = meta->player.direction.x, dirY = meta->player.direction.y; //initial direction vector
	float planeX = meta->data.plane.x, planeY = meta->data.plane.y; //the 2d raycaster version of camera plane

	// printf("Pos: %f %f\n", meta->player.position.x, meta->player.position.y);
	// printf("Dir: %f %f\n", meta->player.direction.x, meta->player.direction.y);
	int w = meta->image->width - 1;
	int h = meta->image->height - 1;

	for(int col = 0; col < w; col++)
    {
      //calculate ray position and direction
      float cameraX = 2 * col / (double)w - 1; //x-coordinate in camera space
      double rayDirX = dirX + planeX * cameraX;
      double rayDirY = dirY + planeY * cameraX;

	  //which box of the map we're in
      int mapX = (int)posX;
      int mapY = (int)posY;

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

       //length of ray from one x or y-side to next x or y-side
      double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
      double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      if (rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if (rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?

	  //perform DDA
      while (hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if (sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = HIT_NS;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = HIT_EW;
        }
        //Check if ray has hit a wall
		
        if (meta->map.level[find_index(meta, mapX, mapY)] == MAP_WALL)
			hit = 1;
      } 
	    //Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
      if(side == 0) perpWallDist = (sideDistX - deltaDistX);
      else          perpWallDist = (sideDistY - deltaDistY);

      //Calculate height of line to draw on screen
      int lineHeight = (int)(h / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + h / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
      if(drawEnd >= h)drawEnd = h - 1;

	int32_t color;

	meta->data.start = (h - lineHeight) / 2;
	if (meta->data.start < 0)
		meta->data.start = 0;
	meta->data.end = (h + lineHeight) / 2;
	if ((int)meta->data.end >= h)
		meta->data.start = h - 1;
	
	// draw_line

	int row = 0;
	// draw_col(meta->image, start, end, color);
	while (row <= (int)h)
	{
		if (row < (int)meta->data.start)
		{
			color = set_color(255, 0, 0, 255);
		}
		else if (row > (int)meta->data.end)
		{
			color = set_color(50, 30, 0, 255);
		}
		else
		{
			color = find_wall_color(side);
		}
		mlx_put_pixel(meta->image, col, row, color);
		row++;
	}
  }
}



void game_loop(void* param)
{
	t_meta *const meta = param;

	raycast_and_render(meta);
}
