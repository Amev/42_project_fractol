/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftol_mousehook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 11:06:00 by vame              #+#    #+#             */
/*   Updated: 2015/03/10 10:42:16 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int					ftol_mouse_motion(int x, int y, t_win *env)
{
	if (env->motion && env->name == JULIA)
	{
		env->c_re = 1.5 * (x - env->w / 2) / (0.5 * env->w * env->zoom);
		env->c_im = (y - env->h / 2) / (0.5 * env->h * env->zoom);
		env->event = 1;
	}
	return (0);
}

static void			ftol_thorn_const_end(t_win *e)
{
	if (e->t_const == 3)
	{
		e->c_re = 0.662;
		e->c_im = 1.086;
	}
	else if (e->t_const == 4)
	{
		e->c_re = -0.354;
		e->c_im = 0.162;
	}
}

static void			ftol_thorn_const(t_win *e, int b)
{
	if (b == 5)
		e->t_const = (e->t_const + 1) % 5;
	else
		e->t_const = e->t_const == 0 ? 5 : e->t_const - 1;
	if (e->t_const == 0)
	{
		e->c_re = 0.102;
		e->c_im = -0.04;
	}
	else if (e->t_const == 1)
	{
		e->c_re = 1.098;
		e->c_im = 1.402;
	}
	else if (e->t_const == 2)
	{
		e->c_re = 9.984;
		e->c_im = 7.550;
	}
	else
		ftol_thorn_const_end(e);
	e->event = 1;
}

int					ftol_mouse_hook(int b, int x, int y,  t_win *e)
{
	//ft_printf("b = %d, x = %d, y = %d.\n", b, x , y);
	if (e->name == THORN && (b == 4 || b == 5))
		ftol_thorn_const(e, b);
	if (b == 1 || b == 3)
	{
		e->move_x += 1.5 * (x - e->w / 2) / (0.5 * e->w * e->zoom);
		e->move_y += (y - e->h / 2) / (0.5 * e->h * e->zoom);
		e->zoom *= b == 1 ? 2 : 0.5;
		e->event = 1;
	}
	return (0);
}
