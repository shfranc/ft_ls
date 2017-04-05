/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 17:40:51 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/05 12:11:57 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	readndisplay_inside(t_file *files_inside, t_opt *option)
{
	t_file *temp;

	if (!option->u_r)
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
			else
			{
				option->l ? display_totalblocks(temp) : 0;
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