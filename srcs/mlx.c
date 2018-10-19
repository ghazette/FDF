/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mlx.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/08 18:20:37 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/01 17:11:37 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fdf.h"

void			get_origins(t_mlx *mlx)
{
	mlx->ox = (mlx->map_origin[0][mlx->mapsizes[0] - 1]->x
		- mlx->map_origin[0][0]->x) / 2;
	mlx->oy = (mlx->map_origin[mlx->mapsizes[1] - 1][0]->y
		- mlx->map_origin[0][0]->y) / 2;
}

t_mlx			*mlx_init_all(int w, int h, char *winname)
{
	t_mlx	*mlx;

	if (!w || !h || !winname)
		return (NULL);
	mlx = (t_mlx*)malloc(sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, w, h, winname);
	mlx->img_data = NULL;
	mlx->img_ptr = NULL;
	mlx->winw = w;
	mlx->winh = h;
	mlx->ox = 0;
	mlx->oy = 0;
	mlx->movex = 0;
	mlx->movey = 0;
	mlx->speed = 15;
	mlx->angley = 0;
	mlx->anglex = 0;
	mlx->anglez = 0;
	mlx->nbpoints = 0;
	mlx->map_display = NULL;
	mlx->map_origin = NULL;
	return (mlx);
}

static void		get_gridsize(char ***grid3d, size_t sizes[2])
{
	size_t w;
	size_t h;

	h = 0;
	w = 0;
	while (grid3d[0][w] != 0)
		w++;
	while (grid3d[h] != 0)
		h++;
	sizes[0] = w;
	sizes[1] = h;
}

static t_vertex	***create_map(char ***grid3d, t_mlx *mlx, size_t i, size_t j)
{
	t_vertex	***map;

	if (!(map = (t_vertex***)malloc(sizeof(t_vertex**) *
	(mlx->mapsizes[1] + 1))))
		return (NULL);
	map[mlx->mapsizes[1]] = 0;
	while (i < mlx->mapsizes[1])
	{
		j = 0;
		if (!(map[i] = (t_vertex**)malloc(sizeof(t_vertex*) *
		(mlx->mapsizes[0] + 1))))
			return (NULL);
		while (j < mlx->mapsizes[0])
		{
			if (!(map[i][j] = (t_vertex*)malloc(sizeof(t_vertex))))
				return (NULL);
			map[i][j]->x = j * 20;
			map[i][j]->y = i * 20;
			map[i][j]->z = ft_atoi(grid3d[i][j]) * 2;
			j++;
		}
		map[i][j] = 0;
		i++;
	}
	return (map);
}

void			*init_map(char ***grid3d, t_mlx *mlx)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	get_gridsize(grid3d, mlx->mapsizes);
	if (!(mlx->map_origin = create_map(grid3d, mlx, i, j)))
		return (NULL);
	if (!(mlx->map_display = create_map(grid3d, mlx, i, j)))
		return (NULL);
	ft_free3d(&grid3d);
	return (mlx->map_origin);
}
