/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftol_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 11:29:21 by vame              #+#    #+#             */
/*   Updated: 2015/03/09 15:58:54 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int					ftol_init_env_variables(t_win *env)
{
	env->max = 0;
	env->zoom = 1;
	env->c_re = env->name == THORN ? 0.102 : -0.7;
	env->c_im = env->name == THORN ? -0.04 : 0.27015;
	env->motion = 0;
	env->event = 0;
	env->move_x = env->name == MANDEL ? 0.2 : 0;
	env->move_y = 0;
	env->iter = env->name == THORN ? 200 : 300;
	env->esc = env->name == THORN ? 32 : 4;
	if (env->name == BUDDHA)
	{
		env->pxl_tmp; = ftol_create_pxl(env->iter, 2);
		env->pxl = ftol_create_pxl(env->w, env->h);
		ftol_clean_pxl(env->w, env->h, &env->pxl);
	}
	ftol_set_color(KEYCODE_1, env);
	return (1);
}

int					ftol_fractal_name(t_win *env, char *ac)
{
	env->name = 0;
	if (!ft_strcmp("julia", ac))
		env->name = JULIA;
	else if (!ft_strcmp("mandel", ac))
		env->name = MANDEL;
	else if (!ft_strcmp("ship", ac))
		env->name = SHIP;
	else if (!ft_strcmp("thorn", ac))
		env->name = THORN;
	else if (!ft_strcmp("buddha", ac))
		env->name = BUDDHA;
	else
		ftol_print_error(ERR_NAM);
	return (1);
}

int					ftol_win_param(t_win *env, int av, char **ac)
{
	int				w;
	int				h;

	w = 0;
	h = 0;
	if (av < 2 || av > 4 || av == 3)
		ftol_print_error(ERR_ARG);
	ftol_fractal_name(env, ac[1]);
	if (av > 2)
	{
		w = ft_atoi(ac[2]);
		h = ft_atoi(ac[3]);
	}
	env->w = w < LIMIT_MIN_W ? LIMIT_MIN_W : w;
	env->w = env->w > LIMIT_MAX_W ? LIMIT_MAX_W : env->w;
	env->h = h < LIMIT_MIN_H ? LIMIT_MIN_H : h;
	env->h = env->h > LIMIT_MAX_H ? LIMIT_MAX_H : env->h;
	return (1);
}