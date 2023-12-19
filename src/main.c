/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <jboeve@student.codam.nl>            +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/11/07 15:28:54 by jboeve        #+#    #+#                 */
/*   Updated: 2023/12/19 00:44:34 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "meta.h"
#include "vector.h"
#include <stdio.h>

typedef struct s_mat3x3
{
	float	data[3][3];
}	t_mat3x3;

t_mat3x3	get_matrix_rotate_z(float angle)
{
	const t_mat3x3	mat = {{
	{cos(angle), -sin(angle), 0},
	{sin(angle), cos(angle), 0},
	{0, 0, 1},
	}};

	return (mat);
}

typedef struct s_point
{
	float		x;
	float		y;
	float		z;
	int32_t		actual_z;
	t_rgba		color;
}	t_point;

t_vec2f	mat1x3mul(t_vec2f point, t_mat3x3 m)
{
	const float	px = point[VEC_X];
	const float	py = point[VEC_Y];

	point[VEC_X] = (px * m.data[0][0]) + (py * m.data[0][1]);
	point[VEC_Y] = (px * m.data[1][0]) + (py * m.data[1][1]);
	return (point);
}


int main(int argc, char *argv[])
{
	float angle = 0.0f;
	t_vec2f x = {1.0f, 1.0f};
	x = x * vec2f_normalize(vec2f_rotate2d(deg_to_rad(angle)));

	t_vec2f y = {1.0f, 1.0f};
	y = vec2f_normalize(mat1x3mul(y, get_matrix_rotate_z(deg_to_rad(angle))));




	print_vec2f("x", x);
	print_vec2f("y", y);

	return (cub3d(argc, argv));
}
