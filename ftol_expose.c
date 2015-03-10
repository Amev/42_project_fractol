/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftol_expose.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 11:15:17 by vame              #+#    #+#             */
/*   Updated: 2015/03/08 17:04:19 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int					ftol_loop_hook(t_win *e)
{
	if (e->event)
		ftol_expose_hook(e);
	e->event = 0;
	return (0);
}

int					ftol_expose_hook(t_win *e)
{
	e->img = mlx_new_image(e->mlx, e->w, e->h);
	e->img_str = mlx_get_data_addr(e->img, &e->bpp, &e->len, &e->endian);
	if (e->name == BUDDHA)
		ftol_buddha(e);
	else
		ftol_draw(e);
	e->event = 0;
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_destroy_image(e->mlx, e->img);
	return (1);
}
