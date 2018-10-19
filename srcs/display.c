/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/01 13:24:31 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/01 15:40:52 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int		rgba(int r, int g, int b, int a)
{
	return ((a << 24) + (r << 16) + (g << 8) + b);
}

static void		display_commands(t_mlx *mlx)
{
	char	*x;
	char	*y;
	char	*z;
	int		c;

	c = rgba(254, 254, 254, 0);
	mlx_string_put(mlx->ptr, mlx->win, 50, 10, c, "--COMMANDS--");
	mlx_string_put(mlx->ptr, mlx->win, 10, 40, c, "numpad 4,6 rotate on Y");
	mlx_string_put(mlx->ptr, mlx->win, 10, 70, c, "numpad 2,8 rotate on X");
	mlx_string_put(mlx->ptr, mlx->win, 10, 100, c, "numpad 7,9 rotate on Z");
	mlx_string_put(mlx->ptr, mlx->win, 10, 130, c, "numpad 1,3 to extrude");
	mlx_string_put(mlx->ptr, mlx->win, 10, 160, c, "mouse wheel to zoom");
	x = ft_itoa((int)mlx->anglex);
	y = ft_itoa((int)mlx->angley);
	z = ft_itoa((int)mlx->anglez);
	mlx_string_put(mlx->ptr, mlx->win, 10, 190, c, "X : ");
	mlx_string_put(mlx->ptr, mlx->win, 50, 190, c, x);
	mlx_string_put(mlx->ptr, mlx->win, 10, 220, c, "Y : ");
	mlx_string_put(mlx->ptr, mlx->win, 50, 220, c, y);
	mlx_string_put(mlx->ptr, mlx->win, 10, 250, c, "Z : ");
	mlx_string_put(mlx->ptr, mlx->win, 50, 250, c, z);
	ft_strdel(&x);
	ft_strdel(&y);
	ft_strdel(&z);
}

void			displayfdf(t_mlx *mlx)
{
	char	*mapsizes;
	int		c;

	c = rgba(254, 254, 254, 0);
	display_commands(mlx);
	mapsizes = ft_itoa(mlx->mapsizes[0] * mlx->mapsizes[1]);
	mlx_string_put(mlx->ptr, mlx->win, 10, 280, c, "Map size : ");
	mlx_string_put(mlx->ptr, mlx->win, 120, 280, c, mapsizes);
	ft_strdel(&mapsizes);
}
