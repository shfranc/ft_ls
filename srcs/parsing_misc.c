/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:19:30 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/13 12:57:39 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	check_arg_vide(int ac, char **av)
{
	struct stat	av_stat;

	while (--ac)
	{
		++av;
		if ((ft_strequ(*av, "")))
		{
			stat("", &av_stat);
			ft_putstr_fd(LS, 2);
			ft_putstr_fd(""":", 2);
			ft_exit(strerror(errno));
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

char	*create_path(char *dir, char *file)
{
	char *path;

	path = ft_strnew(ft_strlen(dir) + ft_strlen(file) + 1);
	path = ft_strcat(ft_strcat(ft_strcpy(path, dir), "/"), file);
	return (path);
}
