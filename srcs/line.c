/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   line.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/07 13:18:58 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/01 13:52:10 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void		set_image_pixel(t_mlx *mlx, int x, int y, t_color *color)
{
	intmax_t	i;

	i = x * (mlx->bpp / 8) + (y * mlx->sizeline);
	mlx->img_data[i] = (char)color->b;
	mlx->img_data[i + 1] = (char)color->g;
	mlx->img_data[i + 2] = (char)color->r;
	mlx->img_data[i + 3] = (char)color->a;
}

static void		init_bresenham(t_bresenham *b, t_vertex *pt, t_vertex *pt2)
{
	b->x2 = (int)pt2->x;
	b->y2 = (int)pt2->y;
	b->x = (int)pt->x;
	b->y = (int)pt->y;
	b->dx = abs(b->x2 - b->x);
	b->sx = b->x < b->x2 ? 1 : -1;
	b->dy = abs(b->y - b->y2);
	b->sy = b->y < b->y2 ? 1 : -1;
	b->err = (b->dx > b->dy ? b->dx : -b->dy) / 2;
}

void			line(t_vertex *pt, t_vertex *pt2, t_mlx *mlx, t_color *color)
{
	t_bresenham b;

	init_bresenham(&b, pt, pt2);
	if (((b.x < 0 || b.x > mlx->winw) || (b.y < 0 || b.y > mlx->winh)) &&
		((b.x2 < 0 || b.x2 > mlx->winw) || (b.y2 < 0 || b.y2 > mlx->winh)))
		return ;
	while (1)
	{
		if (b.x > 0 && b.x < mlx->winw && b.y > 0 && b.y < mlx->winh)
			set_image_pixel(mlx, b.x, b.y, color);
		if (b.x == b.x2 && b.y == b.y2)
			break ;
		b.e2 = b.err;
		if (b.e2 > -b.dx)
		{
			b.err -= b.dy;
			b.x += b.sx;
		}
		if (b.e2 < b.dy)
		{
			b.err += b.dx;
			b.y += b.sy;
		}
	}
}

static void		process(t_mlx *mlx, size_t i, size_t j, t_color *color)
{
	if (mlx->map_display[i][j + 1] != 0)
	{
		set_color(color, mlx->map_origin[i][j]->z,
			mlx->map_origin[i][j + 1]->z);
		line(mlx->map_display[i][j], mlx->map_display[i][j + 1], mlx, color);
	}
	if (mlx->map_display[i + 1] != 0)
	{
		set_color(color, mlx->map_origin[i][j]->z,
			mlx->map_origin[i + 1][j]->z);
		line(mlx->map_display[i][j], mlx->map_display[i + 1][j], mlx, color);
	}
}

void			draw(t_mlx *mlx)
{
	register size_t	i;
	register size_t	j;
	t_color			color;
	int				endian;

	i = 0;
	mlx->img_ptr = mlx_new_image(mlx->ptr, mlx->winw, mlx->winh);
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr, &(mlx->bpp),
		&(mlx->sizeline), &endian);
	while (mlx->map_display[i] != 0)
	{
		j = 0;
		while (mlx->map_display[i][j] != 0)
		{
			process(mlx, i, j, &color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img_ptr, 0, 0);
	displayfdf(mlx);
}
