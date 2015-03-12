/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftol_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 13:17:11 by vame              #+#    #+#             */
/*   Updated: 2015/03/12 15:38:33 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				ftol_print_error(int err)
{
	if (err == ERR_ARG)
	{
		ft_printf("{red}Bad number of arguments.\n");
		ft_printf("{wht}Correct usage is : ");
		ft_printf("\"{grn}./fractol {name} (opt)width (opt)high{wht}\".\n");
		ft_printf("Please specify a name betwen : {grn}{julia");
		ft_printf("/mandel/ship/thorn/multi}{wht}.{eoc}\n");
	}
	else if (err == ERR_MAL)
		ft_printf("{red}Malloc error.{eoc}\n");
	else if (err == ERR_NAM)
	{
		ft_printf("{red}Bad fractal's name.\n");
		ft_printf("{wht}Please specify a name betwen : {grn}{julia");
		ft_printf("/mandel/ship/thorn/multi}{wht}.{eoc}\n");
	}
	else if (err == ERR_THD)
		ft_printf("{red}Thread error.{eoc}\n");
	exit(err);
}

void				ftol_init_im(t_complex *im, t_win *e)
{
	im->half_w = e->w / 2;
	im->half_h = e->h / 2;
	im->div_w = 1.5 / (0.5 * e->w * e->zoom);
	im->div_h = 1 / (0.5 * e->h * e->zoom);
}

void				ftol_putinimg(t_win *e, int x, int y, int color)
{
	int				i;

	i = x * 4 + y * e->len;
	e->img_str[i] = (color & 0xFF);
	e->img_str[i + 1] = (color & 0xFF00) >> 8;
	e->img_str[i + 2] = (color & 0xFF0000) >> 16;
}

int					ftol_idxclr(t_win *e, double i)
{
	double			j;

	j = i * 100 / e->iter;
	if (j < 5)
		return (ft_color_degrade(e->clr.color1, e->clr.color2, j * 20));
	else if (j < 10)
		return (ft_color_degrade(e->clr.color2, e->clr.color3, (j - 5) * 10));
	else if (j < 25)
		return (ft_color_degrade(e->clr.color3, e->clr.color4, (j - 10) * 4));
	else if (j < 50)
		return (ft_color_degrade(e->clr.color4, e->clr.color5, (j - 25) * 4));
	else if (j < 75)
		return (ft_color_degrade(e->clr.color5, e->clr.color6, (j - 50) * 4));
	else if (j <= 100)
		return (ft_color_degrade(e->clr.color6, e->clr.color7, (j - 75) * 4));
	return (e->clr.color7);
}
