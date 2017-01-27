/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:39:52 by sfranc            #+#    #+#             */
/*   Updated: 2017/01/27 15:24:38 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_file	*names;
	t_opt	options;

	names = NULL;
	if (!(arg_vide(ac, av)))
		return (0);
	init_options(&options);
	if ((ac = read_options(ac, &av, &options)) == -1)
		return (0);

	display_options(&options);
	ft_putstr("debut des fichiers : ");
	ft_putendl(*av);
	ft_putstr("nombre de fichiers : ");
	ft_putnbr_endl(ac);
	
	return (0);
}
