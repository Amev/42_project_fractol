/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftol_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 12:32:45 by vame              #+#    #+#             */
/*   Updated: 2015/03/10 17:11:02 by vame             ###   ########.fr       */
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

int					ftol_dwrcrs(t_complex *im, int i, t_win *e)
{
	double			tmp;

	im->z_re = im->n_re;
	im->z_im = im->n_im;
	if (e->name == SHIP)
	{
		im->n_re = im->z_re * im->z_re - im->z_im * im->z_im - im->c_re;
		im->n_im = 2 * ft_abs_db(im->z_re * im->z_im) + im->c_im;
	}
	else if (e->name == THORN)
	{
		im->n_re = im->z_re / cos(im->z_im) + im->c_re;
		im->n_im = im->z_im / sin(im->z_re) + im->c_im;
	}
	else if (e->name == MULTI)
	{
		tmp = pow(im->z_re * im->z_re - im->z_im * im->z_im, 2);
		tmp += 4 * im->z_re * im->z_re * im->z_im * im->z_im;
		im->n_re = (im->z_re * im->z_re - im->z_im * im->z_im) / tmp + im->c_re;
		im->n_im = -2 * im->z_im * im->z_re / tmp + im->c_im;
	}
	else
	{
		im->n_re = im->z_re * im->z_re - im->z_im * im->z_im + im->c_re;
		im->n_im = 2 * im->z_re * im->z_im + im->c_im;
	}
	if (i >= e->iter || im->n_re * im->n_re + im->n_im * im->n_im > e->esc)
		return (i);
	return (ftol_dwrcrs(im, i + 1, e));
}

static void			*ftol_d_q(void *param)
{
	int				x;
	int				y;
	t_super_struct	*s;
	t_win			*e;
	t_complex		im;

	s = (struct s_super_struct *)param;
	e = s->e;
	y = s->xywh[1];
	ftol_init_im(&im, e);
	while (y < s->xywh[3])
	{
		x = s->xywh[0];
		while (x < s->xywh[2])
		{
			im.n_re = (x - im.half_w) * im.div_w + e->move_x;
			im.n_im = (y - im.half_h) * im.div_h + e->move_y;
			im.c_re = e->name != JULIA && e->name != THORN ? im.n_re : e->c_re;
			im.c_im = e->name != JULIA && e->name != THORN ? im.n_im : e->c_im;
			ftol_putinimg(e, x++, y, ftol_idxclr(e, ftol_dwrcrs(&im, 0, e)));
		}
		y++;
	}
	pthread_exit(NULL);
}

int					ftol_draw(t_win *e)
{
	int				i;
	t_super_struct	s[8];
	pthread_t		thread[8];

	i = 0;
	while (i < 8)
	{
		s[i].e = e;
		s[i].xywh[0] = (i % 4) * e->w / 4;
		s[i].xywh[1] = i / 4 * e->h / 2;
		s[i].xywh[2] = e->w / 4 + (i % 4) * e->w / 4;
		s[i].xywh[3] = e->h / 2 + (i / 4) * e->h / 2;
		if (pthread_create(&thread[i], NULL, &ftol_d_q, (void *)&s[i]) == -1)
			ftol_print_error(ERR_THD);
		i++;
	}
	i = 0;
	while (i < 8)
		if (pthread_join(thread[i++], NULL) == -1)
			ftol_print_error(ERR_THD);
	return (1);
}
