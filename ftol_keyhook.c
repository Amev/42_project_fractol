/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftol_keyhook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 11:17:42 by vame              #+#    #+#             */
/*   Updated: 2015/03/10 16:00:34 by vame             ###   ########.fr       */
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

static void			ftol_key_move(int k, t_win *e)
{
	double			move;

	if (k == K_LEFT || k == K_RIGHT)
	{
		move = k == K_LEFT ? e->w / 2 - e->w / 20 : e->w / 2 + e->w / 20;	
		e->move_x += 1.5 * (move - e->w / 2) / (0.5 * e->w * e->zoom);
	}
	else if (k == K_TOP || k == K_BOT)
	{
		move = k == K_TOP ? e->h / 2 - e->h / 20 : e->h / 2 + e->h / 20;	
		e->move_y += (move - e->h / 2) / (0.5 * e->h * e->zoom);
	}
}

int					ftol_key_hook(int k, t_win *e)
{
	if (k == 65307)
		exit(0);
	else if (k == KEYCODE_1 || k == KEYCODE_2 || k == KEYCODE_3)
		ftol_set_color(k, e);
	else if (k == 65453 || k == 65451)
		e->zoom *= k == 65451 ? 2 : 0.5;
	else if (k == 65293)
		e->motion = e->motion ? 0 : 1;
	else if (k == K_LEFT || k == K_TOP || k == K_RIGHT || k == K_BOT)
		ftol_key_move(k, e);
	else if (k == 44 || k == 46)
		e->iter = ft_min(5000, ft_max(1, k == 46 ? e->iter + 1 : e->iter - 1));
	else if (k == 109 || k == 47)
	{
		e->iter = ft_max(1, k == 47 ? e->iter * 1.25 : e->iter * 0.75);
		e->iter = ft_min(5000, e->iter);
	}
	else if (k == 45 || k == 61)
		e->esc = ft_max(4, k == 61 ? e->esc * 2 : e->esc * 0.5);
	else if (k == 65288)
		ftol_init_env_variables(e);
	e->event = 1;
	//ft_printf("esc = %d | iter = %d.\n", e->esc, e->iter);
	return (0);
}
