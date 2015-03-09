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

void				ftol_putinimg(t_win *e, int x, int y, int color)
{
	int				i;

	i = x * 4 + y * e->len;
	e->img_str[i] = (color & 0xFF);
	e->img_str[i + 1] = (color & 0xFF00) >> 8;
	e->img_str[i + 2] = (color & 0xFF0000) >> 16;
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

void				*ftol_draw_quarter(s_structure s)
{
	int				x;
	int				y;
	t_complex		im;

	y = s.xywh[1];
	im.esc = s.e->esc;
	im.iter = s.e->iter;
	im.name = s.e->name;
	im.half_w = s.e->w / 2;
	im.half_h = s.e->h / 2;
	im.div_w = 1.5 / (0.5 * e->w * s.e->zoom);
	im.div_h = 1 / (0.5 * e->h * s.e->zoom);
	while (y < s.xywh[3])
	{
		x = s.xywh[0];
		while (x < s.xywh[2])
		{
			im.n_re = (x - im.half_w) * im.div_w + s.e->move_x;
			im.n_im = (y - im.half_h) * im.div_h + s.e->move_y;
			im.c_re = s.e->name != JULIA && s.e->name != THORN ? im.n_re : s.e->c_re;
			im.c_im = s.e->name != JULIA && s.e->name != THORN ? im.n_im : s.e->c_im;
			ftol_putinimg(s.e, x++, y, ftol_idxclr(s.e, ftol_dwrcrs(&im, 0)));
		}
		y++;
	}
	pthread_exit(NULL);
}

int					ftol_draw(t_win *e)
{
	int				i;
	int				rturn[4];
	pthread_t		thread[4];
	t_super_struct	s_structure;

	i = 0;
	s_structure.e = e;
	while (i < 4)
	{
		s_structure.xywh[0] = (i + 1) / 2 * (e->w / 2);
		s_structure.xywh[1] = i % 2 * (e->h / 2);
		s_structure.xywh[2] = (1 + (i / 2)) * (e->w / 2);
		s_structure.xywh[3] = (1 + (i % 2)) * (e->h / 2);
		if (pthread_create(&thread[i++], NULL, ftol_draw_quarter, s_structure) == -1)
			ftol_print_error(ERR_THD);
	}
	rturn[0] = pthread_join(thread[0], NULL);
	rturn[1] = pthread_join(thread[1], NULL);
	rturn[2] = pthread_join(thread[2], NULL);
	rturn[3] = pthread_join(thread[3], NULL);
	if (rturn[0] == -1 || rturn[1] == -1 || rturn[2] == -1 || rturn[3] == -1)
		ftol_print_error(ERR_THD);
	return (1);
}