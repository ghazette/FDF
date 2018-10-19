/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_update.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/21 15:57:09 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/01 18:49:38 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void			init_rot_value(double value[8], t_mlx *mlx)
{
	double	rad[3];

	rad[0] = mlx->angley * (M_PI / 180);
	rad[1] = mlx->anglex * (M_PI / 180);
	rad[2] = mlx->anglez * (M_PI / 180);
	value[0] = cos(rad[0]);
	value[1] = sin(rad[0]);
	value[2] = cos(rad[1]);
	value[3] = sin(rad[1]);
	value[4] = cos(rad[2]);
	value[5] = sin(rad[2]);
}

static void			rotate(t_mlx *mlx, t_vertex v, double val[6],
	size_t i[2])
{
	mlx->map_display[i[0]][i[1]]->x = ((mlx->map_origin[i[0]][i[1]]->x
	- mlx->ox) * val[0]) + (mlx->map_origin[i[0]][i[1]]->z * -val[1]);
	mlx->map_display[i[0]][i[1]]->y = mlx->map_origin[i[0]][i[1]]->y - mlx->oy;
	mlx->map_display[i[0]][i[1]]->z = ((mlx->map_origin[i[0]][i[1]]->x
	- mlx->ox) * val[1]) + (mlx->map_origin[i[0]][i[1]]->z * val[0]);
	v.x = mlx->map_display[i[0]][i[1]]->x;
	v.y = ((mlx->map_display[i[0]][i[1]]->y) * val[2]) +
	((mlx->map_display[i[0]][i[1]]->z) * val[3]);
	v.z = ((mlx->map_display[i[0]][i[1]]->y) * -val[3]) +
	((mlx->map_display[i[0]][i[1]]->z) * val[2]);
	mlx->map_display[i[0]][i[1]]->x = (v.x * val[4]) + (v.y * val[5]) +
	(mlx->ox + mlx->movex);
	mlx->map_display[i[0]][i[1]]->y = (v.x * -val[5]) + (v.y * val[4]) +
	(mlx->oy + mlx->movey);
}

double				get_angle(int key, double angle)
{
	double theta;

	theta = 1;
	if (key == 86 || key == 91 || key == 92)
		angle -= theta;
	if (key == 88 || key == 84 || key == 89)
		angle += theta;
	if (angle >= 360)
		return (0);
	if (angle < 0)
		return (360 - theta);
	return (angle);
}

void				scale(t_mlx *mlx, int key)
{
	register size_t		inc[2];

	inc[0] = 0;
	while (mlx->map_display[inc[0]] != 0)
	{
		inc[1] = 0;
		while (mlx->map_display[inc[0]][inc[1]] != 0)
		{
			if (key == 4)
			{
				mlx->map_origin[inc[0]][inc[1]]->x *= 2;
				mlx->map_origin[inc[0]][inc[1]]->y *= 2;
				mlx->map_origin[inc[0]][inc[1]]->z *= 2;
			}
			if (key == 5)
			{
				mlx->map_origin[inc[0]][inc[1]]->x /= 2;
				mlx->map_origin[inc[0]][inc[1]]->y /= 2;
				mlx->map_origin[inc[0]][inc[1]]->z /= 2;
			}
			inc[1]++;
		}
		inc[0]++;
	}
}

void				map_update(t_mlx *mlx, int key)
{
	double				value[6];
	t_vertex			v;
	register size_t		inc[2];

	v.x = 0;
	mlx->movex -= (key == 123) ? mlx->speed : 0;
	mlx->movex += (key == 124) ? mlx->speed : 0;
	mlx->movey += (key == 125) ? mlx->speed : 0;
	mlx->movey -= (key == 126) ? mlx->speed : 0;
	inc[0] = 0;
	get_origins(mlx);
	init_rot_value(value, mlx);
	if (mlx->img_ptr)
		mlx_destroy_image(mlx->ptr, mlx->img_ptr);
	while (mlx->map_display[inc[0]] != 0)
	{
		inc[1] = 0;
		while (mlx->map_display[inc[0]][inc[1]] != 0)
		{
			rotate(mlx, v, value, inc);
			inc[1]++;
		}
		inc[0]++;
	}
	draw(mlx);
}
