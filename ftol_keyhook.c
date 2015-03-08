/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftol_keyhook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 11:17:42 by vame              #+#    #+#             */
/*   Updated: 2015/03/08 17:04:18 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void			ftol_set_color_end(t_win *env)
{
	env->clr.color1 = 0x000000;
	env->clr.color2 = 0xFFFFFF;
	env->clr.color3 = 0x000000;
	env->clr.color4 = 0x464646;
	env->clr.color5 = 0x8B8B8B;
	env->clr.color6 = 0xD1D1D1;
	env->clr.color7 = 0xFFFFFF;
}

void				ftol_set_color(int keycode, t_win *env)
{
	if (keycode == KEYCODE_1)
	{
		env->clr.color1 = 0x42170D;
		env->clr.color2 = 0xE09919;
		env->clr.color3 = 0xF1D451;
		env->clr.color4 = 0xD5BB94;
		env->clr.color5 = 0xCDC7B7;
		env->clr.color6 = 0x756155;
		env->clr.color7 = 0x453D38;
	}
	else if (keycode == KEYCODE_2)
	{
		env->clr.color1 = 0x0000FF;
		env->clr.color2 = 0x00FFFF;
		env->clr.color3 = 0x00FF00;
		env->clr.color4 = 0xFBFF00;
		env->clr.color5 = 0xFF671E;
		env->clr.color6 = 0xFF0000;
		env->clr.color7 = 0x000000;
	}
	else if (keycode == KEYCODE_3)
		ftol_set_color_end(env);
}

int					ftol_key_hook(int k, t_win *env)
{
	if (k == 65307)
		exit(0);
	else if (k == KEYCODE_1 || k == KEYCODE_2 || k == KEYCODE_3)
		ftol_set_color(k, env);
	else if (k == 65453)
		env->zoom /= 2;
	else if (k == 65451)
		env->zoom *= 2;
	env->event = 1;
	return (0);
}

int					ftol_mouse_motion(int x, int y, t_win *env)
{
	if (env->motion && env->name == JULIA)
	{
		env->c_re = 1.5 * (x - env->w / 2) / (0.5 * env->w * env->zoom);
		env->c_im = (y - env->h / 2) / (0.5 * env->h * env->zoom);
		env->event = 1;
	}
	else if (env->motion && env->name == MANDEL)
	{
		env->coef_x = (x - env->w / 2) / (0.5 * env->w);
		env->coef_y = (y - env->h / 2) / (0.5 * env->h);
		env->event = 1;
	}
	return (0);
}

int					ftol_mouse_hook(int b, int x, int y,  t_win *env)
{
	(void)env;
	ft_printf("motion = %d, x = %d, y = %d.\n", env->motion, x , y);
	if (b == 1 && !env->motion)
		env->motion = 1;
	else if (b == 1 && env->motion)
		env->motion = 0;
	return (0);
}
