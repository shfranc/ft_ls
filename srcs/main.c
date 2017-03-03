/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:39:52 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/03 17:59:39 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		arg_vide(int ac, char **av)
{
	struct stat	av_stat;

	while (--ac)
	{
		++av;
		if ((ft_strequ(*av, "")))
		{
			stat("", &av_stat);
			ft_putstr(LS);
			ft_putstr(""":");
			perror(*av);
			return (0);
		}
	}
	return (1);
}

int		main(int ac, char **av)
{
	t_file	*names;
	t_opt	options;
//	t_file	*new;

	names = NULL;
	if (!(arg_vide(ac, av)))
		return (0);
	init_options(&options);
	if ((ac = read_options(ac, &av, &options)) == -1)
		return (0);
	read_names(ac, av, &names, &options);
	
	// display_options(&options);
	
	if (options.l)
	{
		ft_putendl("LONG DISPLAY");
		long_display(ac, names, &options);
	}
	else
		classic_display(ac, names, &options);

//	display_options(&options);
//	ft_putstr("debut des fichiers : ");
//	ft_putendl(*av);
//	ft_putstr("nombre de fichiers : ");
//	ft_putnbr_endl(ac);

//	while(1);

	return (0);
}
