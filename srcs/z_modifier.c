/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   z_modifier.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/21 17:47:00 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/01 16:50:00 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	z_modifier(t_mlx *mlx, int key)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (key == 83 || key == 85)
	{
		while (mlx->map_origin[i] != 0)
		{
			j = 0;
			while (mlx->map_origin[i][j] != 0)
			{
				if (key == 83 && mlx->map_origin[i][j]->z != 0)
					mlx->map_origin[i][j]->z += 10.01;
				if (key == 85 && mlx->map_origin[i][j]->z != 0)
					mlx->map_origin[i][j]->z -= 10.01;
				j++;
			}
			i++;
		}
		map_update(mlx, key);
	}
}
