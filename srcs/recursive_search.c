/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 17:40:51 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/10 19:56:14 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	readndisplay_inside(t_file *files_inside, t_opt *option)
{
	t_file *temp;

	if (!option->u_r || not_searchable(files_inside, option))
		return ;
	temp = files_inside;
	while (temp)
	{
		if (!(ft_strequ(temp->name, ".")) && !(ft_strequ(temp->name, ".."))
			&& S_ISDIR(temp->stat.st_mode) && !(S_ISLNK(temp->lstat.st_mode)))
		{
			walk_dir(temp->path, &temp, option);
			write(1, "\n", 1);
			ft_putendl2(temp->path, ":");
			if (temp->error != 0)
				display_file_error(temp);
			else if ((file_list_len(temp->inside)))
			{
				display_totalblocks(temp);
				temp->inside = which_sort(temp->inside, option);
				recursive_display(temp->inside, option);
			}
			readndisplay_inside(temp->inside, option);
		}
		temp = temp->next;
	}
}

void	recursive_display(t_file *files, t_opt *option)
{
	if (option->l)
		long_display_inside(files, option);
	else
		display_inside(files, option);
}

int		not_searchable(t_file *files, t_opt *option)
{
	t_file	*temp;
	int		i;

	i = 0;
	temp = files;
	while (temp)
	{
		if (lstat(temp->path, &temp->lstat) == -1
			&& (option->u_r))
			i++;
		temp = temp->next;
	}
	return (i);
}

int		not_sortable(t_file *files, t_opt *option)
{
	t_file	*temp;
	int		i;

	i = 0;
	temp = files;
	while (temp)
	{
		if (lstat(temp->path, &temp->lstat) == -1
			&& (option->t || option->u_s))
			i++;
		temp = temp->next;
	}
	return (i);
}
