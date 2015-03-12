/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftol_mousehook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 11:06:00 by vame              #+#    #+#             */
/*   Updated: 2015/03/12 13:53:12 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int					ftol_mouse_motion(int x, int y, t_win *env)
{
	if (env->motion && (env->name == JULIA || env->name == THORN))
	{
		env->c_re = 1.5 * (x - env->w / 2) / (0.5 * env->w * env->zoom);
		env->c_im = (y - env->h / 2) / (0.5 * env->h * env->zoom);
		env->event = 1;
	}
	return (0);
}

static int			ftol_rand_color(void)
{
	int				r;
	int				g;
	int				b;

	r = (rand() % 256) << 16;
	g = (rand() % 256) << 8;
	b = rand() % 256;
	return ((r | g) | b);
}

static void			ftol_change_color(t_win *env)
{
	env->clr.color1 = ftol_rand_color();
	env->clr.color2 = ftol_rand_color();
	env->clr.color3 = ftol_rand_color();
	env->clr.color4 = ftol_rand_color();
	env->clr.color5 = ftol_rand_color();
	env->clr.color6 = ftol_rand_color();
	env->clr.color7 = ftol_rand_color();
	env->event = 1;
}

int					ftol_mouse_hook(int b, int x, int y, t_win *e)
{
	if (e->rand && (b == 4 || b == 5))
		ftol_change_color(e);
	if (b == 1 || b == 3)
	{
		e->move_x += 1.5 * (x - e->w / 2) / (0.5 * e->w * e->zoom);
		e->move_y += (y - e->h / 2) / (0.5 * e->h * e->zoom);
		e->zoom *= b == 1 ? 2 : 0.5;
		e->event = 1;
	}
	return (0);
}
