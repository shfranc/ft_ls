/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_part2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 10:47:05 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/30 16:25:52 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		display_non_dir_column(t_file *files, t_opt *option, int nb_file)
{
	t_file	*temp;
	t_file	*cpy;
	t_file	*non_dir;

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
	display_column(non_dir, option);
	free_file(&non_dir);
	return (nb_file);
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
	if (!(elem->name = ft_strdup(path)))
		ft_exit("Unable to malloc path");
	elem->next = NULL;
	elem->inside = NULL;
	return (elem);
}
