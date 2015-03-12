/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftol_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 12:32:45 by vame              #+#    #+#             */
/*   Updated: 2015/03/12 13:54:09 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void			ftol_fractal_algo(t_complex *im, t_win *e)
{
	double			tmp;

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
}

static int			ftol_dwrcrs(t_complex *im, double i, t_win *e)
{
	im->z_re = im->n_re;
	im->z_im = im->n_im;
	if (e->name == SHIP || e->name == THORN || e->name == MULTI)
		ftol_fractal_algo(im, e);
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
	pthread_t		thread[8];
	t_super_struct	s[8];

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
