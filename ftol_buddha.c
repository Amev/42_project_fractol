/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftol_buddha.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 12:32:45 by vame              #+#    #+#             */
/*   Updated: 2015/03/09 15:17:10 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void			ftol_iter_pxl(double **tp, double ***p, int i, t_win *env)
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
			(*p)[y][x] += 1;
			if ((*p)[y][x] > e->max)
				e->max = (*p)[y][x];
		}
	}
}

static void			ftol_draw_buddha(t_win *e, int **pxl)
{
	int				x;
	int				y;
	int				index;
	int				color;

	y = 0;
	while (y++ < e->h)
	{
		x = 0;
		while (x < e->w)
		{
			index = pxl[y - 1][x] * 100 / e->max;
			color = ft_color_degrade(0x000000, 0xFFFFFF, index)
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
	int				**pxl;
	int				**pxl_tmp;

	y = 0;
	ftol_init_im(&im, e);
	while (y < e->h)
	{
		x = 0;
		while (x < e->w)
		{
			i = 0;
			im.z_re = 0;
			im.z_im = 0;
			ftol_clean_pxl(e->iter, 2, &pxl_tmp);
			im.c_re = (x - im.half_w) * im.div_w + e->move_x;
			im.c_im = (y - im.half_h) * im.div_h + e->move_y;
			while (i < e->iter && im.z_re * im.z_re + im.z_im * im.z_im < e->esc)
			{
				im.n_re = im.z_re;
				im.n_im = im.z_im;
				im.z_re = im.n_re * im.n_re + im.n_im * im.n_im + im.c_re;
				im.z_im = 2 * im.n_re * im.n_im + im.c_im;
				pxl_tmp[i][0] = im.z_re;
				pxl_tmp[i++][1] = im.z_im;
			}
			if (i != e->iter)
				ftol_iter_pxl(pxl_tmp, &pxl, i);
		}
	}
	ftol_draw_buddha(e, pxl);
	//free les tableaux;
}