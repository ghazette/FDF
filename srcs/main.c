/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/31 18:34:19 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/01 17:10:51 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/fdf.h"

static void	center(t_mlx *mlx)
{
	get_origins(mlx);
	while ((mlx->ox * 2) > 2300 && (mlx->oy * 2) > 1300)
	{
		scale(mlx, 5);
		get_origins(mlx);
	}
	mlx->movex = (2300 / 2) - mlx->ox;
	mlx->movey = (1300 / 2) - mlx->oy;
}

int			main(int ac, char **av)
{
	t_mlx			*mlx;
	unsigned char	error;
	int				fd;
	char			***grid;

	if (ac == 2)
	{
		if (!(error = grid_checker(av[1], &fd, &grid)))
		{
			mlx = mlx_init_all(2300, 1300, "FdF");
			if (!(init_map(grid, mlx)))
				exit(1);
			center(mlx);
			map_update(mlx, 0);
			mlx_mouse_hook(mlx->win, &dealmouse, mlx);
			mlx_hook(mlx->win, 2, 1L, &deal_key, mlx);
			mlx_loop(mlx->ptr);
		}
		else
			display_errors(error);
	}
	else
		ft_printf("Usage : ./fdf file.fdf\n");
	return (0);
}
