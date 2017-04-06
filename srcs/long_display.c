/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 10:49:12 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/06 19:02:37 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		long_display_non_dir(t_file *files, t_opt *option)
{
	t_file	*temp;
	int		nb_file;
	
	fill_long_format(files, option);
	temp = files;
	nb_file = 0;
	while (temp)
	{
		if ((!S_ISDIR(temp->stat.st_mode) || (S_ISLNK(temp->lstat.st_mode))))
		{
			if (temp->error == 0 || temp->error == 20)
			{
				long_display_path(temp, option);
				nb_file++;
			}
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
				if (!(file_list_len(temp->inside)))
					break ;
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

	if (read_only(files, option))
		return ;
	fill_long_format(files, option);
	temp = files;
	while (temp)
	{
		// if ((lstat(temp->path, &temp->lstat)) == -1)
		// 	display_file_error(temp);
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
		temp = temp->next;
	}
}

void	long_display(int ac, t_file *files, t_opt *option)
{
	int		nb_error;
	int		nb_file;

	files = which_sort(files, option);
	nb_error = display_errors(files);
	nb_file = long_display_non_dir(files, option);
	if (nb_file != 0 && (nb_file + nb_error) != ac)
		write(1, "\n", 1);
	long_display_dir(nb_file + nb_error, ac, files, option);
}

void	long_display_path(t_file *temp, t_opt *option)
{
	write(1, temp->long_format, (temp->len.total));
	if (option->u_g)
	{
		join_color(temp, temp->path);
		ft_putstr(temp->color_name);
	}
	else
		ft_putstr(temp->path);
	if (S_ISLNK(temp->lstat.st_mode))
		ft_putstr(ft_strstr(temp->long_format, "->") - 1);
	write(1, "\n", 1);
}
