/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 10:49:12 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/13 18:24:44 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		long_display_non_dir(t_file *files, t_opt *option)
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
				fill_long_format(files, option);
				long_display_line(temp, option);
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
		if (S_ISDIR(temp->stat.st_mode) && !S_ISLNK(temp->lstat.st_mode))
		{
			if (ac != 1)
				ft_putendl2(temp->path, ":");
			if (temp->error == 13)
				display_file_error(temp);
			else
			{
				display_totalblocks(temp);
				temp->inside = which_sort(temp->inside, option);
				long_display_inside(temp->inside, option);
				readndisplay_inside(temp->inside, option);
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
		long_display_line(temp, option);
		temp = temp->next;
	}
}

void	long_display(int ac, t_file *files, t_opt *option)
{
	int		nb_file;

	display_errors(files);
	files = which_sort(files, option);
	nb_file = long_display_non_dir(files, option);
	if (nb_file != 0 && nb_file != ac)
		write(1, "\n", 1);
	long_display_dir(nb_file, ac, files, option);
}

void	long_display_line(t_file *temp, t_opt *option)
{
	if (option->u_g)
	{
		write(1, temp->long_format, (temp->len.total));
		join_color(temp, temp->name);
		if (S_ISLNK(temp->lstat.st_mode))
			ft_putendl2(temp->color_name,
				ft_strstr(temp->long_format, "->") - 1);
		else
			ft_putendl(temp->color_name);
	}
	else
		ft_putendl(temp->long_format);
}
