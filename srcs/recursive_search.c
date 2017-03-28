/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 17:40:51 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/28 14:21:11 by sfranc           ###   ########.fr       */
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
				display_inside(temp->inside, option);
			}
			readndisplay_inside(temp->inside, option);
		}
		temp = temp->next;
	}
}
