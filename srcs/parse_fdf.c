/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_fdf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/21 15:19:25 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/01 17:08:07 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fdf.h"

char	***to_3d_grid(char **grid)
{
	char	***grid3d;
	size_t	height;
	size_t	i;

	i = 0;
	height = ft_heightlen(grid);
	if (!(grid3d = (char***)malloc(sizeof(char**) * (height + 1))))
		return (NULL);
	grid3d[height] = 0;
	while (i < height)
	{
		if (!(grid3d[i] = ft_strsplit(grid[i], ' ')))
			return (NULL);
		i++;
	}
	return (grid3d);
}

char	*readed_concat(char **readed, char **line)
{
	char *tmp;
	char *new;

	if (!(*readed = ft_safecat(*readed, *line)))
		return (NULL);
	if (!(tmp = ft_strjoin(*readed, "\n")))
		return (NULL);
	ft_strdel(&(*readed));
	if (!(new = ft_strdup(tmp)))
		return (NULL);
	ft_strdel(&tmp);
	ft_strdel(&(*line));
	return (new);
}

char	***get_grid(int fd)
{
	char			*readed;
	char			***grid3d;
	char			**grid;
	char			*line;

	if (!(readed = ft_strnew(0)))
		return (NULL);
	while (get_next_line(fd, &line) != 0)
		if (!(readed = readed_concat(&readed, &line)))
			return (NULL);
	if (!(grid = ft_strsplit(readed, '\n')))
		return (NULL);
	ft_strdel(&readed);
	if (!(grid3d = to_3d_grid(grid)))
		return (NULL);
	ft_free2d(&grid);
	return (grid3d);
}
