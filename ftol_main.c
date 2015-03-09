/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftol_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 11:02:11 by vame              #+#    #+#             */
/*   Updated: 2015/03/09 14:41:42 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int					main(int av, char **ac)
{
	t_win			env;

	env.mlx = mlx_init();
	ftol_win_param(&env, av, ac);
	ftol_init_env_variables(&env);
	env.win = mlx_new_window(env.mlx, env.w, env.h, "fractol");
	mlx_expose_hook(env.win, ftol_expose_hook, &env);
	mlx_hook(env.win, 6, 64, ftol_mouse_motion, &env);
	mlx_key_hook(env.win, ftol_key_hook, &env);
	mlx_mouse_hook(env.win, ftol_mouse_hook, &env);
	mlx_loop_hook(env.mlx, ftol_loop_hook, &env);
	mlx_loop(env.mlx);
	return (1);
}
