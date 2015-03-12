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

void				ftol_printf_menu(t_win *env, char *ac)
{
	ft_printf("{grn}Bienvenu dans fractol, voici le menu de %s:\n", ac);
	ft_printf("Deplacements :{eoc}\n");
	ft_printf("{ylw}Fleche Haut / Bas / Gauche / Droite{eoc} {wht}: ");
	ft_printf("déplacements sur x et y.{eoc}\n");
	ft_printf("{ylw}Pave num +{eoc} {wht}: zoom + central.{eoc}\n");
	ft_printf("{ylw}Pave num -{eoc} {wht}: zoom - central.{eoc}\n");
	ft_printf("{ylw}Clic gauche souris{eoc} {wht}: zoom + sur point.{eoc}\n");
	ft_printf("{ylw}Clic droit souris{eoc} {wht}: zoom - sur point.{eoc}\n");
	ft_printf("{grn}Parametres :{eoc}\n");
	ft_printf("{ylw}+{eoc} {wht}: augmentation de l'echappement.{eoc}\n");
	ft_printf("{ylw}-{eoc} {wht}: diminussion de l'echappement.{eoc}\n");
	ft_printf("{ylw}>{eoc} {wht}: max iteraton + 1.{eoc}\n");
	ft_printf("{ylw}<{eoc} {wht}: max iteraton - 1.{eoc}\n");
	ft_printf("{ylw}m{eoc} {wht}: max iteraton * 0.75.{eoc}\n");
	ft_printf("{ylw};{eoc} {wht}: max iteraton * 1.25.{eoc}\n");
	if (env->name == THORN)
		ft_printf("{ylw}Molette Haut / Bas{wht} : changement cste.{eoc}\n");
	if (env->name == JULIA)
		ft_printf("{ylw}Enter {wht} : activation / desactivation souris.\n");
	ft_printf("{ylw}1, 2 et 3 {wht}: set de couleur 1, 2 et 3.{eoc}\n");
}