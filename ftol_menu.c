/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftol_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 11:02:11 by vame              #+#    #+#             */
/*   Updated: 2015/03/12 15:30:21 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				ftol_print_menu(t_win *env, char *ac)
{
	ft_printf("{grn}Bienvenu dans fractol, voici le menu de %s:\n", ac);
	ft_printf("-----------------------------------------------\n\n");
	ft_printf("Deplacements :\n--------------\n");
	ft_printf("{ylw}Fleche Haut / Bas {wht}: deplacements sur y.\n");
	ft_printf("{ylw}Fleche Gauche / Droite {wht}: deplacements sur x.\n");
	ft_printf("{ylw}Pave num + {wht}: zoom + central.\n");
	ft_printf("{ylw}Pave num - {wht}: zoom - central.\n");
	ft_printf("{ylw}Clic gauche souris {wht}: zoom + sur point.\n");
	ft_printf("{ylw}Clic droit souris {wht}: zoom - sur point.\n\n");
	ft_printf("{grn}Parametres :\n------------\n");
	ft_printf("{ylw}+ {wht}: augmentation de l'echappement.\n");
	ft_printf("{ylw}- {wht}: diminussion de l'echappement.\n");
	ft_printf("{ylw}> {wht}: max iteraton + 1.\n");
	ft_printf("{ylw}< {wht}: max iteraton - 1.\n");
	ft_printf("{ylw}m {wht}: max iteraton * 0.75.\n");
	ft_printf("{ylw}? {wht}: max iteraton * 1.25.\n");
	if (env->name == THORN)
		ft_printf("{ylw}Molette Haut / Bas{wht} : changement cste.\n");
	if (env->name == JULIA)
		ft_printf("{ylw}Enter {wht} : activation / desactivation souris.\n");
	ft_printf("{ylw}Espace  {wht}: activation / desactivation molette.\n");
	ft_printf("{ylw}1, 2 et 3 {wht}: set de couleur 1, 2 et 3.\n");
	ft_printf("{ylw}Molette Haut / Bas {wht}: couleurs aleatoires.\n\n");
	ft_printf("{grn}-----------------------------------------------{eoc}\n");
}
