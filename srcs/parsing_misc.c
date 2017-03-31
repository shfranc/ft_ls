/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:19:30 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/31 17:07:06 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	check_arg_vide(int ac, char **av)
{
	struct stat	av_stat;
	int			ret;

	while (--ac)
	{
		++av;
		if ((ft_strequ(*av, "")))
		{
			if ((ret = stat("", &av_stat)) == -1)
			{
				ft_putstr_fd(LS, 2);
				ft_putstr_fd(""":", 2);
				ft_exit(strerror(errno));
			}

		}
	}
}

int		set_current_dir(int ac, char ***av)
{
	if (ac == 0)
	{
		ac++;
		**av = ".";
	}
	return (ac);
}

void	file_init(t_file *elem)
{
	elem->error = 0;
	elem->path = NULL;
	elem->name = NULL;
	elem->color_name = NULL;
	elem->long_format = NULL;
	elem->usr = NULL;
	elem->grp = NULL;
	elem->next = NULL;
	elem->inside = NULL;
}
