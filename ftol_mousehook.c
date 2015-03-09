/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftol_mousehook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 11:06:00 by vame              #+#    #+#             */
/*   Updated: 2015/03/09 11:44:15 by vame             ###   ########.fr       */
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

int					ftol_mouse_hook(int b, int x, int y,  t_win *e)
{
	ft_printf("b = %d, x = %d, y = %d.\n", b, x , y);
	if (b == 1 || b == 3)
	{
		e->move_x += 1.5 * (x - e->w / 2) / (0.5 * e->w * e->zoom);
		e->move_y += (y - e->h / 2) / (0.5 * e->h * e->zoom);
		e->zoom *= b == 1 ? 2 : 0.5;
		e->event = 1;
	}
	return (0);
}
