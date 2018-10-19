/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/01 14:16:10 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/01 18:14:25 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int		format_checker(char *path)
{
	int		i;
	size_t	len;
	t_error err;

	err = format;
	if (!path)
		return (err);
	i = 0;
	len = ft_strlen(path) - 1;
	while (len > 0)
	{
		if (path[len] == '.')
		{
			if (ft_strstr(path + len, ".fdf"))
				return ((path[len + 4] == '\0') ? 0 : err);
			else
				return (err);
		}
		len--;
	}
	return (err);
}

static int		get_fd(char *path, int *fd)
{
	t_error err;

	err = nofile;
	if ((*fd = open(path, O_RDONLY)) != -1)
		return (0);
	return (nofile);
}

static int		is_correct_grid(char ***grid3d)
{
	t_error	error;
	int		i;
	int		size;

	error = linesize;
	i = 0;
	size = -1;
	while (grid3d[i] != 0)
	{
		if (size == -1)
		{
			size = ft_heightlen(grid3d[i]);
			i++;
			continue;
		}
		if (ft_heightlen(grid3d[i]) != size)
		{
			ft_free3d(&grid3d);
			return (error);
		}
		i++;
	}
	if (size == -1)
		return (error);
	return (0);
}

/*
** error code
** 1 -> WRONG FILE FORMAT (*.fdf)
** 2 -> WRONG CHARACTERS IN FILE
** 4 -> ALL LINE WIDTH IS NOT EQUAL
** 8 -> ALL LINE HEIGHT IS NOT EQUAL
** 16 -> CANNOT OPEN FILE OR DOESN't EXIST
*/

unsigned char	grid_checker(char *path, int *fd, char ****grid)
{
	unsigned char	error;
	char			***grid3d;

	error = 0;
	error += format_checker(path);
	error += get_fd(path, &(*fd));
	if (*fd == -1 || error)
		return (error);
	if (!(grid3d = get_grid(*fd)))
		return (error);
	if ((error += is_correct_grid(grid3d)))
		return (error);
	else
		*grid = grid3d;
	return (error);
}

void			display_errors(unsigned char error)
{
	unsigned char	err;

	ft_printf("Error(s):\n");
	if ((err = error & (0x01 << 0)))
		ft_printf("%#.3x : wrong file format (*.fdf).\n", err);
	if ((err = error & (0x01 << 1)))
		ft_printf("%#.3x : wrong characters in the file.\n", err);
	if ((err = error & (0x01 << 3)))
		ft_printf("%#.3x : the size of each line is not equal.\n", err);
	if ((err = error & (0x01 << 4)))
		ft_printf("%#.3x : unable to open or read the file.\n", err);
}
