/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_R.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 16:31:57 by sfranc            #+#    #+#             */
/*   Updated: 2017/02/06 12:29:52 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	readndisplay_inside(t_file *files_inside, t_opt *options)
{
	t_file *temp;
	int		nb_dir;
	int		i;

	if (options->u_r != 'R')
		return ;
//	ft_putendl("-------- INTERIEUR ");
	i = 0;
	nb_dir = nb_dir_inside(files_inside);
	temp = files_inside;
	while (temp)
	{
		if (!(ft_strequ(ft_strrchr(temp->name, '/') + 1, "."))
				&& !(ft_strequ(ft_strrchr(temp->name, '/') + 1, ".."))
				&& (((temp->stat.st_mode & S_IFMT) ^ S_IFDIR) == 0))
		{
			i++;
//			ft_putendl("-- on fouille ce dossier ");
			walk_dir(temp->name, &temp);
//			ft_putnbr_endl(nb_dir);
//			ft_putnbr_endl(i);
//			write(1, "\n", 1);
			ft_putstr(temp->name);
			ft_putendl(":");
			display_inside(1, 2, temp->inside);
			readndisplay_inside(temp->inside, options);
		}
		temp = temp->next;
	}
//	ft_putendl("fin");
} 

int		nb_dir_inside(t_file *files)
{
	t_file *temp;
	int		dir;

	dir = 0;
	temp = files;
	while (temp)
	{
		if (((temp->stat.st_mode & S_IFMT) ^ S_IFDIR) == 0)
			dir++;
		temp = temp->next;
	}
	return (dir - 2);
}

int		list_file_len(t_file *files, t_opt *options) /* on en aura surement pas besoin */
{
	t_file	*temp;
	int		len;

	len = 0;
	temp = files;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	if (!(options->a))
		len = len - 2;
	return (len);
}
