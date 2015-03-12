/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_degrade.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 10:13:11 by vame              #+#    #+#             */
/*   Updated: 2015/03/12 13:50:13 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_color_degrade_r(int clr_a, int clr_b, double index)
{
	int				r_a;
	int				r_b;
	int				mask;

	mask = 255 << 16;
	r_a = (clr_a & mask) >> 16;
	r_b = (clr_b & mask) >> 16;
	mask = (r_a + ((r_b - r_a) * index / 100));
	mask = mask << 16;
	return (mask);
}

static int			ft_color_degrade_g(int clr_a, int clr_b, double index)
{
	int				g_a;
	int				g_b;
	int				mask;

	mask = 255 << 8;
	g_a = (clr_a & mask) >> 8;
	g_b = (clr_b & mask) >> 8;
	mask = (g_a + ((g_b - g_a) * index / 100));
	mask = mask << 8;
	return (mask);
}

static int			ft_color_degrade_b(int clr_a, int clr_b, double index)
{
	int				b_a;
	int				b_b;
	int				mask;

	mask = 255;
	b_a = clr_a & mask;
	b_b = clr_b & mask;
	return (b_a + ((b_b - b_a) * index / 100));
}

int					ft_color_degrade(int clr_a, int clr_b, double index)
{
	int				r;
	int				g;
	int				b;
	int				color;

	if (index <= 0 || index >= 100)
		return (index < 100 ? clr_a : clr_b);
	r = ft_color_degrade_r(clr_a, clr_b, index);
	g = ft_color_degrade_g(clr_a, clr_b, index);
	b = ft_color_degrade_b(clr_a, clr_b, index);
	color = (r | g) | b;
	return (color);
}
