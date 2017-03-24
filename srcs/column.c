/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 16:03:17 by sfranc            #+#    #+#             */
/*   Updated: 2017/03/24 16:03:19 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		fetch_nb_column(t_file *files)
{
	struct winsize w;
	int	nb_col;
	int	nb_file;

	ioctl(0, TIOCGWINSZ, &w);
	ft_putnbr_endl(w.ws_col);

	nb_col = w.ws_col / set_name_max(files); // un critere si le max est plus grand que la largeur
	nb_file = file_list_len(files);
	ft_putnbr_endl(nb_file);

	// while (nb_col > 0)
	// {
	// 	if (nb_file % nb_col == 0 || nb_file % nb_col == nb_col - 1)
	// 		break ;
	// 	nb_col--;
	// }
	// on se prend un peu la tete la...
	return (nb_col);
}

int		set_name_max(t_file	*files)
{
	t_file	*temp;
	int 	max;

	temp = files;
	max = 0;
	
	while (temp)
	{
		temp->len.size = ft_strlen(temp->name);
		max < temp->len.size ? max = temp->len.size : 0;
		temp = temp->next;
	}
	return (max + 1);
}
