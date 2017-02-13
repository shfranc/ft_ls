/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_upper_r.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 19:20:33 by sfranc            #+#    #+#             */
/*   Updated: 2017/02/13 15:35:06 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	readndisplay_inside(t_file *files_inside, t_opt *options)
{
	t_file *temp;

	if (options->u_r != 'R')
		return ;
	temp = files_inside;
	while (temp)
	{
		if (!(ft_strequ(ft_strrchr(temp->name, '/') + 1, "."))
				&& !(ft_strequ(ft_strrchr(temp->name, '/') + 1, ".."))
				&& (((temp->stat.st_mode & S_IFMT) ^ S_IFDIR) == 0)
				&& (((temp->lstat.st_mode & S_IFMT) ^ S_IFLNK) != 0))
		{
			walk_dir(temp->name, &temp);
			write(1, "\n", 1);
			ft_putstr(temp->name);
			ft_putendl(":");
			if (temp->error != 0)
				display_file_error(temp);
			else
				display_inside(temp->inside);
			readndisplay_inside(temp->inside, options);
		}
		temp = temp->next;
	}
}
