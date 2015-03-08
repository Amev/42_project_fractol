/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 11:03:32 by vame              #+#    #+#             */
/*   Updated: 2015/03/08 16:43:00 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft_ext.h"
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <time.h>
# include <stdio.h>

# define JULIA 1
# define MANDEL 2

# define ERR_ARG 1
# define ERR_MAL 2
# define ERR_NAM 3

# define KEYCODE_1 49
# define KEYCODE_2 50
# define KEYCODE_3 51

# define LIMIT_MIN_W 500
# define LIMIT_MIN_H 400
# define LIMIT_MAX_W 2500
# define LIMIT_MAX_H 1300

# define PI 3.141592653589793

/*
** structure color
*/

typedef struct		s_color
{
	int				color1;
	int				color2;
	int				color3;
	int				color4;
	int				color5;
	int				color6;
	int				color7;
}					t_color;

/*
** structure mlx
*/

typedef struct		s_win
{
	int				w;
	int				h;
	int				name;
	int				motion;
	int				event;
	double			zoom;
	double			c_re;
	double			c_im;
	double			coef_x;
	double			coef_y;
	void			*mlx;
	void			*win;
	void			*img;
	char			*img_str;
	int				bpp;
	int				len;
	int				endian;
	struct s_color	clr;
}					t_win;

int					ftol_key_hook(int k, t_win *env);
void				ftol_set_color(int keycode, t_win *env);
int					ftol_expose_hook(t_win *e);
int					ftol_win_param(t_win *env, int av, char **ac);
int					ftol_fractal_name(t_win *env, char *ac);
int					ftol_draw(t_win *env);
int					ftol_draw_julia(t_win *env);
int					ftol_index_color(t_win *e, int i);
void				ftol_print_into_img(t_win *env, int x, int y, int color);
void				ftol_print_error(int err);
int					ftol_mouse_hook(int b, int x, int y,  t_win *env);
int					ftol_mouse_motion(int x, int y, t_win *env);
int					ftol_loop_hook(t_win *e);

#endif