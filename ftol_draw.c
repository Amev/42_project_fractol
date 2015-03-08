/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftol_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 12:32:45 by vame              #+#    #+#             */
/*   Updated: 2015/03/08 17:04:20 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				ftol_print_into_img(t_win *env, int x, int y, int color)
{
	int				i;

	if (y >= 0 && x >= 0 && x * 4 + y * env->len < env->h * env->len)
	{
		i = x * 4 + y * env->len;
		env->img_str[i] = (color & 0xFF);
		env->img_str[i + 1] = (color & 0xFF00) >> 8;
		env->img_str[i + 2] = (color & 0xFF0000) >> 16;
	}
}

int					ftol_index_color(t_win *e, int i)
{
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

int					ftol_draw_julia(t_win *env)
{
	int				i;
	int				x;
	int				y;
	double			z_re;
	double			z_im;
	double			n_re;
	double			n_im;
	int				color;

	y = 0;
	while (y < env->h)
	{
		x = 0;
		while (x < env->w)
		{
			i = 0;
			n_re = 1.5 * (x - env->w / 2) / (0.5 * env->w * env->zoom);
			n_im = (y - env->h / 2) / (0.5 * env->h * env->zoom);
			if (env->name == MANDEL)
			{
				env->c_re = env->coef_x * n_re;
				env->c_im = env->coef_y * n_im;
			}
			while (i++ < 300)
			{
				z_re = n_re;
				z_im = n_im;
				n_re = z_re * z_re - z_im * z_im + env->c_re;
				n_im = 2 * z_re * z_im + env->c_im;
				if (n_re * n_re + n_im * n_im > 4)
					break;
			}
			color = ftol_index_color(env, i);
			ftol_print_into_img(env, x++, y, color);
		}
		y++;
	}
	return (1);
}

int					ftol_draw(t_win *env)
{
	ftol_draw_julia(env);
	return (1);
}
