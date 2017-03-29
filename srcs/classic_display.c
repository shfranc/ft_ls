/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classic_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 13:00:35 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/29 20:09:15 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		display_non_dir(t_file *files, t_opt *option)
{
	t_file	*temp;
	t_file	*disp;
	int		nb_file;

	temp = files;
	nb_file = 0;
	disp = NULL;
	while (temp)
	{
		if (((temp->stat.st_mode & S_IFMT) ^ S_IFDIR) != 0)
		{
			if (temp->error == 0 || temp->error == 20)
			{
				if (!option->c1)
					file_add_last(&disp, temp);
				if (option->u_g)
				{
					join_color(temp, temp->path);
					ft_putendl(temp->color_name);
				}
				else
					ft_putendl(temp->path);
			}
			nb_file++;
		}
		temp = temp->next;
	}
	if (!option->c1)
		display_column(disp, option);
	return (nb_file);
}

void	display_dir(int nb_file, int ac, t_file *files, t_opt *option)
{
	t_file	*temp;

	temp = files;
	while (temp)
	{
		if (((temp->stat.st_mode & S_IFMT) ^ S_IFDIR) == 0)
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
				display_inside(temp->inside, option);
				readndisplay_inside(temp->inside, option);
			}
			if (++nb_file != ac)
				write(1, "\n", 1);
		}
		temp = temp->next;
	}
}

void	display_inside(t_file *files, t_opt *option)
{
	t_file	*temp;

	if (option->l)
	{
		long_display_inside(files, option);
		return ;
	}
	if (!option->c1)
		display_column(files, option);
	else
	{
		temp = files;
		while (temp)
		{
			if (option->u_g)
			{
				join_color(temp, temp->name);
				ft_putendl(temp->color_name);
			}
			else
				ft_putendl(temp->name);
			temp = temp->next;
		}
	}
}

void	classic_display(int ac, t_file *files, t_opt *option)
{
	int		nb_file;

	display_errors(files);
	files = which_sort(files, option);
	nb_file = display_non_dir(files, option);
	if (nb_file != 0 && nb_file != ac)
		write(1, "\n", 1);
	display_dir(nb_file, ac, files, option);
}
