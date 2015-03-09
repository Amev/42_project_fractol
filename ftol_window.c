/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftol_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 11:29:21 by vame              #+#    #+#             */
/*   Updated: 2015/03/08 16:39:57 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int					ftol_fractal_name(t_win *env, char *ac)
{
	env->name = 0;
	env->zoom = 1;
	env->c_re = -0.7;
	env->c_im = 0.27015;
	env->coef_x = 1;
	env->coef_y = 1;
	env->motion = 0;
	env->event = 0;
	if (!ft_strcmp("julia", ac))
		env->name = JULIA;
	if (!ft_strcmp("mandel", ac))
		env->name = MANDEL;
	if (!ft_strcmp("ship", ac))
		env->name = SHIP;
	if (env->name == 0)
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
