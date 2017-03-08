/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:39:52 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/08 18:27:39 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_file	*files;
	t_opt	option;

	files = NULL;
	check_arg_vide(ac, av);
	init_options(&option);
	ac = read_options(ac, &av, &option);
	read_names(ac, av, &files, &option);
	
	// display_option(&option);
	
	if (option.l)
		long_display(ac, files, &option);
	else
		classic_display(ac, files, &option);


//	while(1);

	return (0);
}
