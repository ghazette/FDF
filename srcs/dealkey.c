/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dealkey.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/26 18:29:21 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/01 11:18:37 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	rotate_zoom(t_mlx *mlx, int key)
{
	if (key == 89 || key == 92)
	{
		mlx->anglez = get_angle(key, mlx->anglez);
		map_update(mlx, key);
	}
	if (key == 84 || key == 91)
	{
		mlx->anglex = get_angle(key, mlx->anglex);
		map_update(mlx, key);
	}
	if (key == 86 || key == 88)
	{
		mlx->angley = get_angle(key, mlx->angley);
		map_update(mlx, key);
	}
}

int			deal_key(int key, void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx*)param;
	z_modifier(mlx, key);
	rotate_zoom(mlx, key);
	if (key == 53)
	{
		write(1, "EXIT PROGRAM.\n", 14);
		exit(0);
	}
	if (key >= 123 && key <= 126)
		map_update(mlx, key);
	return (1);
}

int			dealmouse(int key, int x, int y, void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx*)param;
	if (key == 4)
	{
		scale(mlx, key);
		mlx->movex -= x - (int)mlx->movex;
		mlx->movey -= y - (int)mlx->movey;
		map_update(mlx, key);
	}
	if (key == 5)
	{
		scale(mlx, key);
		mlx->movex += (x - (int)mlx->movex) / 2;
		mlx->movey += (y - (int)mlx->movey) / 2;
		map_update(mlx, key);
	}
	return (1);
}
