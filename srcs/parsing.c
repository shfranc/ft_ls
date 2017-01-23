/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:42:55 by sfranc            #+#    #+#             */
/*   Updated: 2017/01/23 18:53:38 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		read_names(int ac, char **av, t_list **names)
{
	t_list			*temp;
	struct stat		stat_file;
	int				ret_stat;
	char			*errors;
	int				nb_err;

	errors = 0;
	nb_err = 0;
	ft_putendl("--> read_names debut");
	while (ac)
	{
		ret_stat = stat(*av, &stat_file);
		temp = ft_lstnew(*av, ft_strlen(*av));
		if (*names != NULL)
			ft_lstadd(names, temp);
		else
			*names = temp;
		if (errno != 0)
		{
			nb_err++;
			ft_putendl(strerror(errno));
			set_errors(&errors, strerror(errno), *av, nb_err);
		}
		if (ac--)
			av++;
	}
	put_errors(errors, nb_err);
	ft_putendl("--> read_names fin");
}

int		parsing(int ac, char **av, t_list **names, char *options)
{
	(void)options;
	if (ac == 1)
	{
//		ft_putendl("read_names 1");
		read_names(ac, av, names);
	}
	while (--ac)
	{
		++av;
		if (**av != '-')
		{
//			ft_putendl("read_names 2");
			read_names(ac, av, names);
			return (1);
		}
		else
		{
			if (ft_strequ(*av, "--"))
			{
//				ft_putendl("skip -- && read_names 3");
				read_names(--ac, ++av, names);
				return (1);
			}
//			ft_putendl("read_options");
		}
	}
	return (0);
}
