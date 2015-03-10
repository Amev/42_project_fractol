/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftol_buddha.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 12:32:45 by vame              #+#    #+#             */
/*   Updated: 2015/03/10 13:00:42 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void			ftol_iter_pxl(double **tp, double ***p, int i, t_win *e)
{
	int				j;
	int				x;
	int				y;

	j = 0;
	while (j < i)
	{
		x = (tp[j][0] - e->move_x) / (1.5 / (0.5 * e->w * e->zoom)) + e->w / 2;
		y = (tp[j++][0] - e->move_y) / (1 / (0.5 * e->h * e->zoom)) + e->h / 2;
		if (x >= 0 && x < e->w && y >= 0 && y < e->h)
		{
			e->in += 1;
			(*p)[y][x] += 1;
			if ((*p)[y][x] > e->max)
				e->max = (*p)[y][x];
		}
		else
			e->out += 1;
	}
}

static void			ftol_draw_buddha(t_win *e, double **pxl)
{
	int				x;
	int				y;
	int				index;
	int				color;

	y = 0;
	//printf("zoom = %f, out = %d, in = %d.\n", e->zoom, e->out, e->in);
	while (y++ < e->h)
	{
		x = 0;
		while (x < e->w)
		{
			index = pxl[y - 1][x] * 100 / e->max;
			color = ft_color_degrade(0x000000, 0xFFFFFF, index);
			ftol_putinimg(e, x++, y - 1, color);
		}
	}
}

void				ftol_buddha(t_win *e)
{
	int				x;
	int				y;
	int				i;
	t_complex		im;

	y = 0;
	e->in = 0;
	e->out = 0;
	ft_printf("a");
	ftol_init_im(&im, e);
	ft_printf("b");
	ft_printf("c");
	//printf("zoom = %f, out = %d, in = %d.\n", e->zoom, e->out, e->in);
	while (y < e->h)
	{
		x = 0;
		//ft_printf("{red}\n-------------------------------------------------\n");
		while (x < e->w)
		{
			i = 0;
			im.z_re = 0;
			im.z_im = 0;
		//	ft_printf("{grn}e");
			ftol_clean_pxl(e->iter, 2, &e->pxl_tmp);
		//	ft_printf("f");
			im.c_re = (x - im.half_w) * im.div_w + e->move_x;
			im.c_im = (y - im.half_h) * im.div_h + e->move_y;
		//	ft_printf("g");
			while (i < e->iter && im.z_re * im.z_re + im.z_im * im.z_im < e->esc)
			{
				im.n_re = im.z_re;
				im.n_im = im.z_im;
		//		ft_printf("{ylw}h");
				im.z_re = im.n_re * im.n_re - im.n_im * im.n_im + im.c_re;
				im.z_im = 2 * im.n_re * im.n_im + im.c_im;
		//		ft_printf("i");
				e->pxl_tmp[i][0] = im.z_re;
				e->pxl_tmp[i][1] = im.z_im;
				i++;
			}
		//	ft_printf("{grn}j");
			ft_printf("i = %d, iter = %d.\n", i, e->iter);
			if (i != e->iter)
				ftol_iter_pxl(e->pxl_tmp, &e->pxl, i, e);
			x++;
		}
		y++;
	}
	ft_printf("{eoc}k");
	ftol_draw_buddha(e, e->pxl);
	ft_printf("l");
}
