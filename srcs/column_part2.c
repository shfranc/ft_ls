/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_part2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 10:47:05 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/11 19:32:47 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		display_non_dir_column(t_file *files, t_opt *option)
{
	t_file	*temp;
	t_file	*cpy;
	t_file	*non_dir;
	int		nb_file;

	nb_file = 0;
	non_dir = NULL;
	temp = files;
	while (temp)
	{
		if (!S_ISDIR(temp->stat.st_mode)
			&& (temp->error == 0 || temp->error == 20))
		{
			cpy = copy_file(temp->path);
			file_add_last(&non_dir, cpy);
			nb_file++;
		}
		temp = temp->next;
	}
	colunm_or_one_file(non_dir, option);
	free_file(&non_dir);
	return (nb_file);
}

void	colunm_or_one_file(t_file *non_dir, t_opt *option)
{
	if (non_dir && file_list_len(non_dir) > 1)
		display_column(non_dir, option);
	else if (non_dir && option->u_g)
	{
		join_color(non_dir, non_dir->path);
		ft_putendl(non_dir->color_name);
	}
	else if (non_dir)
		ft_putendl(non_dir->path);
}

t_file	*copy_file(char *path)
{
	t_file	*elem;
	int		ret_lstat;

	if (!(elem = (t_file*)malloc(sizeof(t_file))))
		ft_exit("Unable to malloc t_file");
	elem->error = 0;
	if ((ret_lstat = lstat(path, &elem->lstat)) == -1)
		elem->error = errno;
	if (!(elem->path = ft_strdup(path)))
		ft_exit("Unable to malloc path");
	if (!(elem->name = ft_strdup(path)))
		ft_exit("Unable to malloc path");
	elem->next = NULL;
	elem->inside = NULL;
	return (elem);
}
