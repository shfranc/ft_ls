/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 14:19:05 by sfranc            #+#    #+#             */
/*   Updated: 2017/01/16 17:40:09 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** fonctions opendir, readdir, closedir autorisees
** pour ecrire un programme qui ouvre un dossier et liste les fichiers au'il contient.
*/

#include <dirent.h>
#include "libft.h"

int		main(int ac, char **av)
{
	DIR				*dir_ptr;
	struct dirent	*dir_temp;
	int				ret_close;	

	(void)ac;
	if (!(dir_ptr = opendir(av[1])))
		return (0);
	while ((dir_temp = readdir(dir_ptr)) != NULL)
	{
		if (*dir_temp->d_name != '.')
			ft_putendl(dir_temp->d_name);
	}
	if ((ret_close = closedir(dir_ptr) != 0))
		return (0);
	return (0);
}

