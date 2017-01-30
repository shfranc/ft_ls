/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:39:52 by sfranc            #+#    #+#             */
/*   Updated: 2017/01/30 19:11:45 by sfranc           ###   ########.fr       */
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
	read_names(ac, av, &names);
	display_names(ac, names);

//	display_options(&options);
//	ft_putstr("debut des fichiers : ");
//	ft_putendl(*av);
//	ft_putstr("nombre de fichiers : ");
//	ft_putnbr_endl(ac);

//	while (1); /* pour verifier les leaks */
	return (0);
}
