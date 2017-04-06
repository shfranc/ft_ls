/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 11:22:55 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/06 19:02:36 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	free_file(t_file **files)
{
	t_file	*delete;

	if (!files)
		return ;
	while (*files)
	{
		delete = *files;
		*files = (*files)->next;
		if (delete->inside)
			free_file(&delete->inside);
		del_file(delete);
		free(delete);
	}
	*files = NULL;
}

void	del_file(t_file *file)
{
	file->path ? free(file->path) : 0;
	file->color_name ? free(file->color_name) : 0;
	file->long_format ? free(file->long_format) : 0;
}
