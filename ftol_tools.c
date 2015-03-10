/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftol_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 13:17:11 by vame              #+#    #+#             */
/*   Updated: 2015/03/10 13:07:39 by vame             ###   ########.fr       */
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
	else if (err == ERR_MAL)
		ft_printf("{red}Malloc error.{eoc}\n");
	else if (err == ERR_NAM)
	{
		ft_printf("{red}Bad fractal's name.\n");
		ft_printf("Please specify a name betwen : {\"julia\"");
		ft_printf("/\"mandel\"/\"ship\"/\"thorn\"}.{eoc}\n");
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
