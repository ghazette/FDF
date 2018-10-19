/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fdf.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/01 14:39:41 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/01 15:09:39 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../minilibx_macos/mlx.h"
# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>

typedef struct	s_color
{
	short int	r;
	short int	g;
	short int	b;
	short int	a;
}				t_color;

typedef struct	s_vertex
{
	double		x;
	double		y;
	double		z;
}				t_vertex;

typedef struct	s_mlx
{
	void		*ptr;
	void		*win;
	double		ox;
	double		oy;
	int			winw;
	int			winh;
	double		angley;
	double		anglex;
	double		anglez;
	double		movex;
	double		movey;
	int			speed;
	int			bpp;
	int			sizeline;
	int			nbpoints;
	void		*img_ptr;
	char		*img_data;
	size_t		mapsizes[2];
	t_vertex	***map_display;
	t_vertex	***map_origin;
}				t_mlx;

typedef struct	s_bresenham
{
	int x;
	int y;
	int x2;
	int y2;
	int	dx;
	int dy;
	int err;
	int e2;
	int sx;
	int sy;
}				t_bresenham;

typedef enum	e_error
{
	format = 0x01,
	chars = 0x02,
	linesize = 0x08,
	nofile = 0x10
}				t_error;

t_mlx			*mlx_init_all(int w, int h, char *winname);
void			get_origins(t_mlx *mlx);
void			*init_map(char ***grid3d, t_mlx *mlx);
unsigned char	grid_checker(char *path, int *fd, char ****grid);
char			***get_grid(int fd);
char			*readed_concat(char **readed, char **line);
char			***to_3d_grid(char **grid);
void			display_errors(unsigned char error);
void			line(t_vertex *pt, t_vertex *pt2, t_mlx *mlx, t_color *color);
void			draw(t_mlx *mlx);
double			get_angle(int key, double angle);
int				deal_key(int key, void *param);
int				dealmouse(int key, int x, int y, void *param);
void			z_modifier(t_mlx *mlx, int key);
void			set_color(t_color *color, double z, double z1);
void			map_update(t_mlx *mlx, int key);
void			scale(t_mlx *mlx, int key);
void			displayfdf(t_mlx *mlx);

#endif
