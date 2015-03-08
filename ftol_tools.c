/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftol_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 13:17:11 by vame              #+#    #+#             */
/*   Updated: 2015/03/08 13:28:52 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				ftol_print_error(int err)
{
	if (err == ERR_ARG)
	{
		ft_printf("{red}Bad number of arguments.\n");
		ft_printf("Correct usage is : ");
		ft_printf("\"./fractol {name} (opt)width (opt)high\".{eoc}\n");
	}
	if (err == ERR_MAL)
		ft_printf("{red}Malloc error.{eoc}\n");
	if (err == ERR_NAM)
	{
		ft_printf("{red}Bad fractal's name.\n");
		ft_printf("Please specify a name betwen : {julia}.{eoc}\n");
	}
	exit(err);
}
