/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 10:49:12 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/07 19:07:36 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		long_display_non_dir(t_file *files)
{
	t_file	*temp;
	int		nb_file;

	temp = files;
	nb_file = 0;
	while (temp)
	{
		if (((temp->stat.st_mode & S_IFMT) ^ S_IFDIR) != 0
				|| ((temp->lstat.st_mode & S_IFMT) ^ S_IFLNK) == 0)
		{
			if (temp->error == 0 || temp->error == 20)
			{
				ft_putstr(temp->long_format);
				ft_putendl(temp->path);
			}
			nb_file++;
		}
		temp = temp->next;
	}
	return (nb_file);
}

void	long_display_dir(int nb_file, int ac, t_file *files, t_opt *option)
{
	t_file	*temp;

	temp = files;
	while (temp)
	{
		if (((temp->stat.st_mode & S_IFMT) ^ S_IFDIR) == 0
				&& ((temp->lstat.st_mode & S_IFMT) ^ S_IFLNK) != 0)
		{
			if (ac != 1)
			{
				ft_putstr(temp->path);
				ft_putendl(":");
			}
			if (temp->error == 13)
				display_file_error(temp);
			else
			{
				temp->inside = which_sort(temp->inside, option);
				long_display_inside(temp->inside, option);

				readndisplay_inside(temp->inside, option); // y'aura un truc a faire
			}
			if (++nb_file != ac)
				write(1, "\n", 1);
		}
		temp = temp->next;
	}
}

void	long_display_inside(t_file *files, t_opt *option)
{
	t_file	*temp;

	fill_long_format(files, option);
	temp = files;
	while (temp)
	{
		ft_putendl(temp->long_format);
		temp = temp->next;
	}
}

void	long_display(int ac, t_file *files, t_opt *option)
{
	int		nb_file;

	display_errors(files);
	nb_file = long_display_non_dir(files);
	if (nb_file != 0 && nb_file != ac)
		write(1, "\n", 1);
	long_display_dir(nb_file, ac, files, option);
}