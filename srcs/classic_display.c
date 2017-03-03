/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classic_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 13:00:35 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/03 13:07:48 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		display_non_dir(t_file *files)
{
	t_file	*temp;
	int		nb_file;

	temp = files;
	nb_file = 0;
	while (temp)
	{
		if (((temp->stat.st_mode & S_IFMT) ^ S_IFDIR) != 0)
		{
			if (temp->error == 0 || temp->error == 20)
				ft_putendl(temp->name);
			nb_file++;
		}
		temp = temp->next;
	}
	return (nb_file);
}

void	display_dir(int nb_file, int ac, t_file *files, t_opt *options)
{
	t_file	*temp;

	temp = files;
	while (temp)
	{
		if (((temp->stat.st_mode & S_IFMT) ^ S_IFDIR) == 0)
		{
			if (ac != 1)
			{
				ft_putstr(temp->name);
				ft_putendl(":");
			}
			if (temp->error == 13)
				display_file_error(temp);
			else
			{
				temp->inside = which_sort(temp->inside, options);
				display_inside(temp->inside, options);
				readndisplay_inside(temp->inside, options);
			}
			if (++nb_file != ac)
				write(1, "\n", 1);
		}
		temp = temp->next;
	}
}

void	display_inside(t_file *files, t_opt *options)
{
	t_file	*temp;

	if (options->l)
		long_display_inside(files, options);
	else
	{
		temp = files;
		while (temp)
		{
			ft_putendl(ft_strrchr(temp->name, '/') + 1);
			temp = temp->next;
		}
	}
}

void	classic_display(int ac, t_file *files, t_opt *options)
{
	int		nb_file;

	display_errors(files);
	nb_file = display_non_dir(files);
	if (nb_file != 0 && nb_file != ac)
		write(1, "\n", 1);
	display_dir(nb_file, ac, files, options);
}
