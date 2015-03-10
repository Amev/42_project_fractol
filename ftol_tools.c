/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftol_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 13:17:11 by vame              #+#    #+#             */
/*   Updated: 2015/03/08 13:28:52 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				ftol_print_error(int err)
{
	if (err == ERR_ARG)
	{
		ft_printf("{red}Bad number of arguments.\n");
		ft_printf("Correct usage is : ");
		ft_printf("\"./fractol {name} (opt)width (opt)high\".{eoc}\n");
	}
	if (err == ERR_MAL)
		ft_printf("{red}Malloc error.{eoc}\n");
	if (err == ERR_NAM)
	{
		ft_printf("{red}Bad fractal's name.\n");
		ft_printf("Please specify a name betwen : {\"julia\"");
		ft_printf("/\"mandel\"/\"ship\"/\"thorn\"/\"buddha\"}.{eoc}\n");
	}
	exit(err);
}

double				**ftol_create_pxl(int x, int y)
{
	int				i;
	int				**pxl;

	i = 0;
	if (!(pxl = (int **)malloc(sizeof(int *) * y)))
		ftol_print_error(ERR_MAL);
	while (i < y)
		if (!(pxl[i++] = (int *)malloc(sizeof(int) * x)))
			ftol_print_error(ERR_MAL);
	return (pxl);
}

void				ftol_clean_pxl(int x, int y, int ***pxl)
{
	int				i;
	int				j;

	j = 0;
	while (j < y)
	{
		i = 0;
		while (i < x && (*pxl)[j][i])
			(*pxl)[j][i++] = 0;
		j++;
	}
}

void				ftol_init_im(t_complex *im, t_win *e)
{
	im->half_w = e->w / 2;
	im->half_h = e->h / 2;
	im->div_w = 1.5 / (0.5 * e->w * e->zoom);
	im->div_h = 1 / (0.5 * e->h * e->zoom);
}