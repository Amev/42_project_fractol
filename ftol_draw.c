/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftol_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 12:32:45 by vame              #+#    #+#             */
/*   Updated: 2015/03/09 15:17:10 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				ftol_putinimg(t_win *env, int x, int y, int color)
{
	int				i;

	i = x * 4 + y * env->len;
	env->img_str[i] = (color & 0xFF);
	env->img_str[i + 1] = (color & 0xFF00) >> 8;
	env->img_str[i + 2] = (color & 0xFF0000) >> 16;
}

int					ftol_idxclr(t_win *e, int i)
{
	i = i * 300 / e->iter;
	if (i < 26)
		return (ft_color_degrade(e->clr.color1, e->clr.color2, i * 4));
	else if (i < 51)
		return (ft_color_degrade(e->clr.color2, e->clr.color3, (i - 25) * 4));
	else if (i < 76)
		return (ft_color_degrade(e->clr.color3, e->clr.color4, (i - 50) * 4));
	else if (i < 101)
		return (ft_color_degrade(e->clr.color4, e->clr.color5, (i - 75) * 4));
	else if (i < 201)
		return (ft_color_degrade(e->clr.color5, e->clr.color6, (i - 100)));
	else if (i < 301)
		return (ft_color_degrade(e->clr.color6, e->clr.color7, (i - 200)));
	return (e->clr.color7);
}

int					ftol_dwrcrs(t_complex *im, int i)
{
	im->z_re = im->n_re;
	im->z_im = im->n_im;
	if (im->name == SHIP)
	{
		im->n_re = im->z_re * im->z_re - im->z_im * im->z_im - im->c_re;
		im->n_im = 2 * ft_abs_db(im->z_re * im->z_im) + im->c_im;
	}
	else if (im->name == THORN)
	{
		im->n_re = im->z_re / cos(im->z_im) + im->c_re;
		im->n_im = im->z_im / sin(im->z_re) + im->c_im;
	}
	else
	{
		im->n_re = im->z_re * im->z_re - im->z_im * im->z_im + im->c_re;
		im->n_im = 2 * im->z_re * im->z_im + im->c_im;
	}
	if (i >= im->iter || im->n_re * im->n_re + im->n_im * im->n_im > im->esc)
		return (i);
	return (ftol_dwrcrs(im, i + 1));
}

int					ftol_draw(t_win *e)
{
	int				x;
	int				y;
	t_complex		im;

	y = 0;
	im.esc = e->esc;
	im.iter = e->iter;
	im.name = e->name;
	im.half_w = e->w / 2;
	im.half_h = e->h / 2;
	im.div_w = 1.5 / (0.5 * e->w * e->zoom);
	im.div_h = 1 / (0.5 * e->h * e->zoom);
	while (y < e->h)
	{
		x = 0;
		while (x < e->w)
		{
			im.n_re = (x - im.half_w) * im.div_w + e->move_x;
			im.n_im = (y - im.half_h) * im.div_h + e->move_y;
			im.c_re = e->name != JULIA && e->name != THORN ? im.n_re : e->c_re;
			im.c_im = e->name != JULIA && e->name != THORN ? im.n_im : e->c_im;
			ftol_putinimg(e, x++, y, ftol_idxclr(e, ftol_dwrcrs(&im, 0)));
		}
		y++;
	}
	return (1);
}
