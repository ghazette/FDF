/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   color.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/26 09:50:34 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/01 15:49:39 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	set_color(t_color *color, double z, double z1)
{
	color->r = 20;
	color->g = 118;
	color->b = 254;
	color->a = 0;
	if (z >= 0 && z1 >= 1)
	{
		color->r = 0;
		color->g = (254 - z1 >= 50) ? 254 - z1 : 50;
		color->b = 0;
		return ;
	}
	if (z >= 1 && z1 >= 0)
	{
		color->r = 0;
		color->g = (254 - z >= 50) ? 254 - z : 50;
		color->b = 0;
	}
}
