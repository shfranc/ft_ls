/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_R.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 16:31:57 by sfranc            #+#    #+#             */
/*   Updated: 2017/02/01 18:57:45 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	readndisplay_inside(int ac, t_file *files_inside, t_opt *options)
{
	t_file *temp;
	int		nb_file;

	(void)ac;
	nb_file = 0;
	if (options->u_r != 'R')
		return ;
	ft_putendl("-------- INTERIEUR ");
	temp = files_inside;
	while (temp)
	{
		ft_putendl(temp->name);
		if (!(ft_strstr(temp->name, ".")) && !(ft_strstr(temp->name, ".."))
						&& (((temp->stat.st_mode & S_IFMT) ^ S_IFDIR) == 0))
		{
			ft_putstr("-- on fouille ce dossier ");
			ft_putendl(temp->name);
			walk_dir(temp->name, &temp);
//			classic_display(ac, temp, options);
//			nb_file = list_file_len(temp->inside);
//			printf("%s\t%d", temp->name, nb_file);
//			display_inside(nb_file, ac, temp->inside);
//			readndisplay_inside(ac, temp->inside, options);
		}
		temp = temp->next;
	}
	ft_putendl("fin");
} 

int		list_file_len(t_file *files)
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
	return (len);
}
